#!/usr/bin/env bash
# =============================================================================
#  Testes para o ex01 (RPN - Reverse Polish Notation)
#
#  Uso:
#     ./tests/test_ex01.sh                 -> testa o teu ex01
#     ./tests/test_ex01.sh /caminho/ex01   -> testa o ex01 de outra pessoa
#
#  Cada teste mostra: o comando, o que é esperado, o que o programa deu,
#  e o exit code. Crashes e timeouts aparecem a vermelho.
# =============================================================================

DIR="${1:-$(dirname "$0")/../ex01}"
DIR="$(cd "$DIR" 2>/dev/null && pwd)" || { echo "Pasta não encontrada: $1"; exit 1; }
NAME="RPN"
BIN="$DIR/$NAME"

B=$'\e[1m'; G=$'\e[32m'; Y=$'\e[33m'; RD=$'\e[31m'; C=$'\e[36m'; R=$'\e[0m'
total=0; crashes=0

section() { printf '\n%s%s=== %s ===%s\n' "$B" "$Y" "$1" "$R"; }

report() {
    local code=$1
    if [ "$code" -eq 124 ]; then
        printf '  %s⏱  TIMEOUT: ficou preso mais de 10s%s\n' "$RD" "$R"; crashes=$((crashes+1))
    elif [ "$code" -gt 128 ] && [ "$code" -le 192 ]; then
        printf '  %s💥 CRASH: sinal %d (SIG%s)%s\n' "$RD" $((code-128)) "$(kill -l $((code-128)))" "$R"; crashes=$((crashes+1))
    else
        printf '  exit code: %d\n' "$code"
    fi
}

# t "descrição" "esperado" [args...]
t() {
    local desc="$1" exp="$2"; shift 2
    total=$((total+1))
    printf '\n%s▶ %s%s\n' "$B" "$desc" "$R"
    printf '  %scomando :%s ./%s' "$C" "$R" "$NAME"
    for a in "$@"; do printf ' "%s"' "$(printf '%s' "$a" | sed 's/\t/\\t/g')"; done; printf '\n'
    printf '  %sesperado:%s %s\n' "$C" "$R" "$exp"
    local out code
    out=$(timeout 10 "$BIN" "$@" 2>&1); code=$?
    printf '  %sobtido  :%s %s\n' "$C" "$R" "$(printf '%s' "$out" | head -n 5)"
    report "$code"
}

# ----------------------------------------------------------------------------
section "Compilação"
( cd "$DIR" && make re 2>&1 | tail -5 )
grep -q -- '^[^#]*CXXFLAGS.*-Wall.*-Wextra.*-Werror.*-std=c++98' "$DIR/Makefile" \
    && printf '  %s✅ Makefile tem -Wall -Wextra -Werror -std=c++98%s\n' "$G" "$R" \
    || printf '  %s❌ Makefile NÃO usa -Wall -Wextra -Werror -std=c++98%s\n' "$RD" "$R"
[ -x "$BIN" ] || { printf '%sO executável %s não existe. A parar.%s\n' "$RD" "$BIN" "$R"; exit 1; }

# ----------------------------------------------------------------------------
section "Exemplos do subject"
t "exemplo 1" "42" "8 9 * 9 - 9 - 9 - 4 - 1 +"
t "exemplo 2" "42" "7 7 * 7 -"
t "exemplo 3" "0"  "1 2 * 2 / 2 * 2 4 - +"
t "exemplo 4 (parênteses)" "Error" "(1 + 1)"

# ----------------------------------------------------------------------------
section "Argumentos"
t "sem argumentos" "Error"
t "dois argumentos" "Error" "1 2 +" "3 4 +"
t "string vazia" "Error" ""
t "só espaços" "Error" "     "

# ----------------------------------------------------------------------------
section "Contas válidas"
t "um número sozinho" "1" "1"
t "zero sozinho" "0" "0"
t "soma" "3" "1 2 +"
t "subtração com resultado negativo" "-1" "1 2 -"
t "multiplicação" "72" "8 9 *"
t "divisão inteira" "2" "5 2 /"
t "divisão com negativo (trunca para zero)" "-4" "0 9 - 2 /"
t "zero a dividir" "0" "0 5 /"
t "operadores todos seguidos no fim" "45" "1 2 3 4 5 6 7 8 9 + + + + + + + +"
t "exemplo da Wikipedia" "14" "5 1 2 + 4 * + 3 -"
t "vários espaços entre tokens" "3" "1     2    +"
t "tabs entre tokens" "3 (ou Error, mas sem crash)" $'1\t2\t+'
t "espaços no início e no fim" "3" "   1 2 +   "
t "resultado grande mas válido (9^9)" "387420489" "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"

# ----------------------------------------------------------------------------
section "Divisão por zero (CRASH comum!)"
t "1 / 0" "Error" "1 0 /"
t "0 / 0" "Error" "0 0 /"
t "divisor que DÁ zero (5 / (3-3))" "Error" "5 3 3 - /"

# ----------------------------------------------------------------------------
section "Overflow (resultado não cabe num int)"
t "9^10 (passa de INT_MAX)" "Error (ou o valor certo 3486784401 se usares long)" "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"
t "9^11" "Error (ou o valor certo 31381059609)" "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"
t "negativo muito grande" "Error (ou o valor certo)" "0 9 - 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"
t "soma enorme" "Error (ou o valor certo)" "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * +"

# ----------------------------------------------------------------------------
section "Expressões mal formadas"
t "operador sem números" "Error" "+"
t "operador com 1 número" "Error" "1 +"
t "operador no início" "Error" "+ 1 2"
t "números a mais (sobra 1 na pilha)" "Error" "1 2"
t "operadores a mais" "Error" "1 2 + +"
t "notação normal (infixa)" "Error" "1 + 2"

# ----------------------------------------------------------------------------
section "Tokens inválidos"
t "número >= 10" "Error" "10 2 +"
t "número negativo como token" "Error" "-1 2 +"
t "número com sinal +" "Error" "+1 2 +"
t "decimal" "Error" "1.5 2 +"
t "letra" "Error" "a 2 +"
t "operador desconhecido (%)" "Error" "1 2 %"
t "operador desconhecido (^)" "Error" "2 3 ^"
t "sem espaços (12+)" "Error (ou 3, ser coerente)" "12+"
t "operador colado a número (+3)" "Error" "1 2 +3"
t "dois operadores colados (++)" "Error" "1 2 3 ++"
t "parênteses no meio" "Error" "1 2 ( +"
t "caractere estranho" "Error" "1 2 + ;"

# ----------------------------------------------------------------------------
section "Expressões compridas"
long=""; for i in $(seq 1 5000); do long="$long 1"; done; for i in $(seq 1 4999); do long="$long +"; done
t "5000 números e 4999 somas" "5000" "$long"

# ----------------------------------------------------------------------------
printf '\n%s=== RESUMO ===%s\n' "$B" "$R"
printf '  testes: %d\n' "$total"
if [ "$crashes" -eq 0 ]; then printf '  %s0 crashes/timeouts%s\n' "$G" "$R"
else printf '  %s%d crashes/timeouts%s\n' "$RD" "$crashes" "$R"; fi
printf '  Confirma também que os erros vão para o stderr: ./%s "1 +" 2>/dev/null não deve mostrar nada.\n' "$NAME"
