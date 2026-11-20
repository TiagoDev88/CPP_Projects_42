#!/usr/bin/env bash
# =============================================================================
#  Testes para o ex02 (PmergeMe - Ford-Johnson)
#
#  Uso:
#     ./tests/test_ex02.sh                 -> testa o teu ex02
#     ./tests/test_ex02.sh /caminho/ex02   -> testa o ex02 de outra pessoa
#
#  Os testes de ordenação são verificados AUTOMATICAMENTE (✅/❌):
#  compara a linha "After:" com o resultado do `sort -n`.
#  Os testes de erro mostram o esperado vs obtido para leres.
# =============================================================================

DIR="${1:-$(dirname "$0")/../ex02}"
DIR="$(cd "$DIR" 2>/dev/null && pwd)" || { echo "Pasta não encontrada: $1"; exit 1; }
NAME="PmergeMe"
BIN="$DIR/$NAME"

B=$'\e[1m'; G=$'\e[32m'; Y=$'\e[33m'; RD=$'\e[31m'; C=$'\e[36m'; R=$'\e[0m'
total=0; crashes=0; ok=0; ko=0

section() { printf '\n%s%s=== %s ===%s\n' "$B" "$Y" "$1" "$R"; }

report() {
    local code=$1
    if [ "$code" -eq 124 ]; then
        printf '  %s⏱  TIMEOUT: ficou preso mais de 20s%s\n' "$RD" "$R"; crashes=$((crashes+1)); return 1
    elif [ "$code" -gt 128 ] && [ "$code" -le 192 ]; then
        printf '  %s💥 CRASH: sinal %d (SIG%s)%s\n' "$RD" $((code-128)) "$(kill -l $((code-128)))" "$R"; crashes=$((crashes+1)); return 1
    fi
    printf '  exit code: %d\n' "$code"
}

# err "descrição" "esperado" [args...]   -> casos de erro / input estranho
err() {
    local desc="$1" exp="$2"; shift 2
    total=$((total+1))
    printf '\n%s▶ %s%s\n' "$B" "$desc" "$R"
    printf '  %scomando :%s ./%s' "$C" "$R" "$NAME"
    for a in "$@"; do printf ' "%s"' "$a"; done; printf '\n'
    printf '  %sesperado:%s %s\n' "$C" "$R" "$exp"
    local out code
    out=$(timeout 20 "$BIN" "$@" 2>&1); code=$?
    printf '  %sobtido  :%s\n' "$C" "$R"
    printf '%s\n' "$out" | head -n 6 | cut -c1-120 | sed 's/^/      /'
    report "$code"
}

# sorted "descrição" [args...]   -> verifica automaticamente a ordenação
sorted() {
    local desc="$1"; shift
    total=$((total+1))
    printf '\n%s▶ %s%s  (%d números)\n' "$B" "$desc" "$R" "$#"
    local out code
    out=$(timeout 20 "$BIN" "$@" 2>&1); code=$?
    report "$code" || { ko=$((ko+1)); return; }

    local expected after before nlines
    expected="After: $(printf '%s\n' "$@" | sort -n | tr '\n' ' ' | sed 's/ $//')"
    before="Before: $*"
    after=$(printf '%s\n' "$out" | grep -m1 '^After:' | sed 's/[[:space:]]*$//')
    nlines=$(printf '%s\n' "$out" | wc -l)

    local fail=0
    [ "$after" = "$expected" ] || { printf '  %s❌ "After:" não está certo%s\n' "$RD" "$R"; fail=1; }
    [ "$(printf '%s\n' "$out" | grep -m1 '^Before:' | sed 's/[[:space:]]*$//')" = "$before" ] \
        || { printf '  %s❌ "Before:" não mostra a sequência original%s\n' "$RD" "$R"; fail=1; }
    [ "$nlines" -eq 4 ] || { printf '  %s⚠️  output tem %d linhas (o subject pede 4)%s\n' "$Y" "$nlines" "$R"; }
    printf '%s\n' "$out" | grep -q 'vector\|deque\|list' \
        || printf '  %s⚠️  as linhas de tempo não dizem o nome do contentor%s\n' "$Y" "$R"

    if [ $fail -eq 0 ]; then
        ok=$((ok+1)); printf '  %s✅ ordenado corretamente%s\n' "$G" "$R"
    else
        ko=$((ko+1))
        printf '  esperado: %s\n' "$(printf '%s' "$expected" | cut -c1-110)"
        printf '  obtido  : %s\n' "$(printf '%s' "$after" | cut -c1-110)"
    fi
    printf '%s\n' "$out" | grep -i 'time' | sed 's/^/      /'
}

# ----------------------------------------------------------------------------
section "Compilação"
( cd "$DIR" && make re 2>&1 | tail -5 )
grep -q -- '^[^#]*CXXFLAGS.*-Wall.*-Wextra.*-Werror.*-std=c++98' "$DIR/Makefile" \
    && printf '  %s✅ Makefile tem -Wall -Wextra -Werror -std=c++98%s\n' "$G" "$R" \
    || printf '  %s❌ Makefile NÃO usa -Wall -Wextra -Werror -std=c++98%s\n' "$RD" "$R"
[ -x "$BIN" ] || { printf '%sO executável %s não existe. A parar.%s\n' "$RD" "$BIN" "$R"; exit 1; }

# ----------------------------------------------------------------------------
section "Erros (devem ir para o stderr)"
err "sem argumentos" "Error"
err "exemplo do subject: -1 2" "Error" "-1" "2"
err "zero" "Error (0 não é positivo) - decisão a justificar" "0"
err "zero no meio" "Error" "3" "0" "5"
err "letras" "Error" "abc"
err "número com letra" "Error" "12a"
err "sinal +" "Error (ou aceitar, ser coerente)" "+5"
err "argumento vazio" "Error" ""
err "decimal" "Error" "4.2"
err "INT_MAX (2147483647)" "aceitar e ordenar" "2147483647" "1"
err "INT_MAX + 1" "Error" "2147483648"
err "número gigante (overflow de long)" "Error" "99999999999999999999"
err "zeros à esquerda (00042)" "aceitar como 42 (ou Error, ser coerente)" "00042" "7"
err "espaços à volta (\"   9\")" "aceitar o 9, ou Error - decisão a justificar" "   9" "3"
err "vários números num argumento (\"3 5 9\")" "aceitar como 3 números, ou Error - decisão a justificar" "3 5 9 7 4"
err "erro no fim de 3000 números válidos" "Error (sem imprimir Before/After)" $(shuf -i 1-100000 -n 3000) "x"

total=$((total+1))
printf '\n%s▶ os erros vão para o stderr?%s\n' "$B" "$R"
if [ -z "$("$BIN" "-1" 2>/dev/null)" ]; then
    ok=$((ok+1)); printf '  %s✅ nada no stdout quando há erro%s\n' "$G" "$R"
else
    ko=$((ko+1)); printf '  %s❌ a mensagem de erro aparece no stdout (devia ser std::cerr)%s\n' "$RD" "$R"
fi

# ----------------------------------------------------------------------------
section "Ordenação: casos pequenos (onde costumam aparecer bugs)"
sorted "exemplo do subject" 3 5 9 7 4
sorted "1 número" 42
sorted "2 números ordenados" 1 2
sorted "2 números trocados" 2 1
sorted "3 números" 3 1 2
sorted "4 números" 4 3 2 1
sorted "5 números" 5 1 4 2 3
for n in 6 7 8 9 10 11 12 13 16 17 21 22 23 33 43 44 64 65; do
    sorted "$n números aleatórios" $(shuf -i 1-1000 -n "$n")
done

section "Ordenação: casos especiais"
sorted "já ordenado" $(seq 1 50)
sorted "ordem inversa" $(seq 50 -1 1)
sorted "todos iguais" $(for i in $(seq 1 21); do echo 7; done)
sorted "repetidos (5 5 3 5 1)" 5 5 3 5 1
sorted "muitos repetidos" $(shuf -i 1-5 -n 100 -r)
sorted "pares iguais" 2 2 1 1 3 3 4 4
sorted "INT_MAX com outros" 2147483647 1 2147483646 2
sorted "alternado alto/baixo" 1 100 2 99 3 98 4 97 5 96 6

section "Ordenação: tamanhos grandes"
sorted "3000 aleatórios (como no subject)" $(shuf -i 1-100000 -n 3000)
sorted "3000 com repetidos" $(shuf -i 1-100 -n 3000 -r)
sorted "3000 já ordenados" $(seq 1 3000)
sorted "3000 ao contrário" $(seq 3000 -1 1)
sorted "10000 aleatórios" $(shuf -i 1-1000000 -n 10000)

section "Muitos testes aleatórios"
fails_before=$ko
for i in $(seq 1 100); do
    n=$(( (RANDOM % 200) + 1 ))
    args=$(shuf -i 1-500 -n "$n" -r)
    out=$(timeout 20 "$BIN" $args 2>&1); code=$?
    exp="After: $(printf '%s\n' $args | sort -n | tr '\n' ' ' | sed 's/ $//')"
    got=$(printf '%s\n' "$out" | grep -m1 '^After:' | sed 's/[[:space:]]*$//')
    total=$((total+1))
    if [ "$code" -gt 128 ] || [ "$got" != "$exp" ]; then
        ko=$((ko+1)); printf '  %s❌ falhou com: %s%s\n' "$RD" "$(echo $args | cut -c1-100)" "$R"
    else
        ok=$((ok+1))
    fi
done
[ $ko -eq $fails_before ] && printf '  %s✅ 100 sequências aleatórias (1 a 200 números, com repetidos) certas%s\n' "$G" "$R"

# ----------------------------------------------------------------------------
printf '\n%s=== RESUMO ===%s\n' "$B" "$R"
printf '  testes: %d   ✅ %d   ❌ %d\n' "$total" "$ok" "$ko"
if [ "$crashes" -eq 0 ]; then printf '  %s0 crashes/timeouts%s\n' "$G" "$R"
else printf '  %s%d crashes/timeouts%s\n' "$RD" "$crashes" "$R"; fi
printf '  Verifica também à mão: tempos com precisão suficiente para ver a diferença entre contentores.\n'
