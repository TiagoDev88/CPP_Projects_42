#!/usr/bin/env bash
# =============================================================================
#  Testes para o ex00 (btc - Bitcoin Exchange)
#
#  Uso:
#     ./tests/test_ex00.sh                 -> testa o teu ex00
#     ./tests/test_ex00.sh /caminho/ex00   -> testa o ex00 de outra pessoa
#
#  Cada teste mostra: o comando, o que é esperado, o que o programa deu,
#  e o exit code. Crashes e timeouts aparecem a vermelho.
#  O "esperado" é o comportamento mais seguro na avaliação; em alguns casos
#  há mais do que uma resposta aceitável (está indicado).
# =============================================================================

DIR="${1:-$(dirname "$0")/../ex00}"
DIR="$(cd "$DIR" 2>/dev/null && pwd)" || { echo "Pasta não encontrada: $1"; exit 1; }
NAME="btc"
BIN="$DIR/$NAME"

B=$'\e[1m'; G=$'\e[32m'; Y=$'\e[33m'; RD=$'\e[31m'; C=$'\e[36m'; R=$'\e[0m'
TMP="$(mktemp -d)"
trap 'chmod -R u+rw "$TMP" 2>/dev/null; rm -rf "$TMP"' EXIT
total=0; crashes=0; n=0

section() { printf '\n%s%s=== %s ===%s\n' "$B" "$Y" "$1" "$R"; }

# report <exit code>
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

# run "descrição" "esperado" comando [args...]   (corre dentro da pasta do ex00)
run() {
    local desc="$1" exp="$2"; shift 2
    total=$((total+1))
    printf '\n%s▶ %s%s\n' "$B" "$desc" "$R"
    printf '  %scomando :%s %s\n' "$C" "$R" "$*"
    printf '  %sesperado:%s %s\n' "$C" "$R" "$exp"
    local out code
    out=$(cd "$DIR" && timeout 10 "$@" 2>&1); code=$?
    printf '  %sobtido  :%s\n' "$C" "$R"
    printf '%s\n' "$out" | head -n 20 | sed 's/^/      /'
    report "$code"
}

# fcase "descrição" "esperado" "conteúdo do ficheiro (aceita \n, \t, \r)"
fcase() {
    local desc="$1" exp="$2" content="$3"
    n=$((n+1))
    local f="$TMP/case$n.txt"
    printf '%b' "$content" > "$f"
    printf '\n%s   conteúdo do ficheiro:%s\n' "$C" "$R"
    # cat -A mostra os invisíveis: $ = fim de linha, ^I = tab, ^M = \r
    printf '%b' "$content" | cat -A | head -n 8 | cut -c1-90 | sed 's/^/      | /'
    run "$desc" "$exp" "$BIN" "$f"
}

# ----------------------------------------------------------------------------
section "Compilação"
( cd "$DIR" && make re 2>&1 | tail -5 )
grep -q -- '^[^#]*CXXFLAGS.*-Wall.*-Wextra.*-Werror.*-std=c++98' "$DIR/Makefile" \
    && printf '  %s✅ Makefile tem -Wall -Wextra -Werror -std=c++98%s\n' "$G" "$R" \
    || printf '  %s❌ Makefile NÃO usa -Wall -Wextra -Werror -std=c++98 (linha comentada?)%s\n' "$RD" "$R"
[ -x "$BIN" ] || { printf '%sO executável %s não existe. A parar.%s\n' "$RD" "$BIN" "$R"; exit 1; }

# ----------------------------------------------------------------------------
section "Argumentos"
run "sem argumentos" "Error: could not open file. (igual ao subject)" "$BIN"
run "ficheiro que não existe" "Error: could not open file." "$BIN" "nao_existe.txt"
run "dois argumentos" "erro (o subject pede UM ficheiro)" "$BIN" "input.txt" "input.txt"
run "uma pasta em vez de ficheiro" "Error: could not open file. (ou outro erro, mas sem crash)" "$BIN" "/tmp"
touch "$TMP/sem_permissao.txt"; chmod 000 "$TMP/sem_permissao.txt"
run "ficheiro sem permissão de leitura" "Error: could not open file." "$BIN" "$TMP/sem_permissao.txt"

# ----------------------------------------------------------------------------
section "Exemplo do subject"
fcase "input do subject" \
"2011-01-03 => 3 = 0.9 / => 2 = 0.6 / => 1 = 0.3 / => 1.2 = 0.36 / 2011-01-09 => 1 = 0.32 / Error: not a positive number. / Error: bad input => 2001-42-42 / 2012-01-11 => 1 = 7.1 / Error: too large a number." \
"date | value\n2011-01-03 | 3\n2011-01-03 | 2\n2011-01-03 | 1\n2011-01-03 | 1.2\n2011-01-09 | 1\n2012-01-11 | -1\n2001-42-42\n2012-01-11 | 1\n2012-01-11 | 2147483648\n"

# ----------------------------------------------------------------------------
section "Ficheiro vazio / header"
fcase "ficheiro vazio" "nada, ou um erro (sem crash)" ""
fcase "só o header" "nada" "date | value\n"
fcase "sem header (1ª linha já é dados)" "processar 2011-01-03 => 1 = 0.3, ou erro de header" "2011-01-03 | 1\n2011-01-03 | 2\n"
fcase "header errado" "Error: bad input => data | valor (ou ignorar)" "data | valor\n2011-01-03 | 1\n"
fcase "header repetido a meio" "Error: bad input => date | value" "date | value\n2011-01-03 | 1\ndate | value\n"

# ----------------------------------------------------------------------------
section "Valores"
fcase "valor 0" "2011-01-03 => 0 = 0" "date | value\n2011-01-03 | 0\n"
fcase "valor 1000 (limite)" "2011-01-03 => 1000 = 300" "date | value\n2011-01-03 | 1000\n"
fcase "valor 1000.01" "Error: too large a number." "date | value\n2011-01-03 | 1000.01\n"
fcase "valor 2147483648" "Error: too large a number." "date | value\n2011-01-03 | 2147483648\n"
fcase "valor gigante" "Error: too large a number." "date | value\n2011-01-03 | 999999999999999999999999999\n"
fcase "valor -1" "Error: not a positive number." "date | value\n2011-01-03 | -1\n"
fcase "valor -0" "=> 0 = 0, ou not a positive number (NÃO '-0 = -0')" "date | value\n2011-01-03 | -0\n"
fcase "valor 1.5" "2011-01-03 => 1.5 = 0.45" "date | value\n2011-01-03 | 1.5\n"
fcase "valor .5" "=> 0.5 = 0.15, ou bad input" "date | value\n2011-01-03 | .5\n"
fcase "valor 5." "=> 5 = 1.5, ou bad input" "date | value\n2011-01-03 | 5.\n"
fcase "valor +5" "=> 5 = 1.5, ou bad input" "date | value\n2011-01-03 | +5\n"
fcase "valor 1e3 (notação científica)" "bad input (ou 1000 = 300)" "date | value\n2011-01-03 | 1e3\n"
fcase "valor 0x10 (hexadecimal)" "Error: bad input" "date | value\n2011-01-03 | 0x10\n"
fcase "valor nan" "Error: bad input (NÃO 'nan = nan')" "date | value\n2011-01-03 | nan\n"
fcase "valor inf" "Error: bad input ou too large" "date | value\n2011-01-03 | inf\n"
fcase "valor 1a" "Error: bad input" "date | value\n2011-01-03 | 1a\n"
fcase "valor 1 2" "Error: bad input" "date | value\n2011-01-03 | 1 2\n"
fcase "valor 1,5 (vírgula)" "Error: bad input" "date | value\n2011-01-03 | 1,5\n"
fcase "valor vazio" "Error: bad input" "date | value\n2011-01-03 | \n"
fcase "valor só com espaços" "Error: bad input" "date | value\n2011-01-03 |    \n"
fcase "espaço DEPOIS do valor" "2011-01-03 => 3 = 0.9 (o espaço é invisível, muitos avaliadores testam)" "date | value\n2011-01-03 | 3 \n"

# ----------------------------------------------------------------------------
section "Formato da linha"
fcase "sem espaços à volta do |" "processar, ou bad input (ser coerente)" "date | value\n2011-01-03|1\n"
fcase "dois |" "Error: bad input" "date | value\n2011-01-03 | 1 | 2\n"
fcase "só |" "Error: bad input => |" "date | value\n|\n"
fcase "data vazia" "Error: bad input" "date | value\n | 1\n"
fcase "vírgula em vez de |" "Error: bad input" "date | value\n2011-01-03,1\n"
fcase "linha sem |" "Error: bad input => 2011-01-03" "date | value\n2011-01-03\n"
fcase "espaços ANTES da data" "processar, ou bad input" "date | value\n   2011-01-03 | 1\n"
fcase "tabs em vez de espaços" "processar, ou bad input (sem crash)" "date | value\n2011-01-03\t|\t1\n"
fcase "linha só com espaços" "Error: bad input, ou ignorar" "date | value\n     \n2011-01-03 | 1\n"
fcase "linhas vazias a meio" "ignorar as vazias, processar as outras" "date | value\n\n2011-01-03 | 1\n\n\n2011-01-03 | 2\n"
fcase "fim de linha Windows (\\r\\n)" "processar normalmente (ou bad input, sem crash)" "date | value\r\n2011-01-03 | 1\r\n"
fcase "última linha sem \\n" "processar a última linha" "date | value\n2011-01-03 | 1\n2011-01-03 | 2"
fcase "linha muito comprida" "Error: bad input (sem crash)" "date | value\n2011-01-03 | $(printf '1%.0s' {1..5000})\n"

# ----------------------------------------------------------------------------
section "Datas"
fcase "dia e mês sem zero (2011-1-3)" "Error: bad input" "date | value\n2011-1-3 | 1\n"
fcase "barras (2011/01/03)" "Error: bad input" "date | value\n2011/01/03 | 1\n"
fcase "mês 13" "Error: bad input" "date | value\n2011-13-01 | 1\n"
fcase "mês 00" "Error: bad input" "date | value\n2011-00-10 | 1\n"
fcase "dia 00" "Error: bad input" "date | value\n2011-01-00 | 1\n"
fcase "dia 32" "Error: bad input" "date | value\n2011-01-32 | 1\n"
fcase "31 de abril" "Error: bad input" "date | value\n2011-04-31 | 1\n"
fcase "29 fev, ano NÃO bissexto (2011)" "Error: bad input" "date | value\n2011-02-29 | 1\n"
fcase "29 fev, ano bissexto (2012)" "2012-02-29 => 1 = ..." "date | value\n2012-02-29 | 1\n"
fcase "29 fev 1900 (NÃO bissexto: divisível por 100)" "Error: bad input" "date | value\n1900-02-29 | 1\n"
fcase "29 fev 2000 (bissexto: divisível por 400)" "data válida, mas antes da DB -> erro de data" "date | value\n2000-02-29 | 1\n"
fcase "letras na data" "Error: bad input" "date | value\nabcd-ef-gh | 1\n"
fcase "ano com 5 dígitos" "Error: bad input" "date | value\n20110-01-03 | 1\n"
fcase "ano negativo" "Error: bad input" "date | value\n-011-01-03 | 1\n"
fcase "data com hora" "Error: bad input" "date | value\n2011-01-03 10:00 | 1\n"
fcase "lixo depois da data" "Error: bad input" "date | value\n2011-01-03x | 1\n"

# ----------------------------------------------------------------------------
section "Procura na base de dados"
fcase "antes da 1ª data da DB (2009-01-02)" "erro (não há data anterior), sem crash" "date | value\n2009-01-01 | 1\n"
fcase "exatamente a 1ª data da DB" "2009-01-02 => 1 = 0" "date | value\n2009-01-02 | 1\n"
fcase "data entre duas datas da DB" "usa a data ANTERIOR (2011-01-09 => 1 = 0.32 no subject)" "date | value\n2011-01-09 | 1\n"
fcase "data no futuro" "usa a ÚLTIMA data da DB" "date | value\n2030-01-01 | 1\n"
fcase "muitas linhas (10000)" "processa todas sem ficar lento" "date | value\n$(for i in $(seq 1 10000); do printf '2012-01-11 | 1\\n'; done)"

# ----------------------------------------------------------------------------
section "Base de dados (data.csv)"
total=$((total+1))
printf '\n%s▶ correr fora da pasta (sem data.csv na pasta atual)%s\n' "$B" "$R"
printf '  %sesperado:%s erro a dizer que não abre a base de dados, sem crash\n' "$C" "$R"
out=$(cd "$TMP" && timeout 10 "$BIN" "$DIR/input.txt" 2>&1); code=$?
printf '  %sobtido  :%s\n' "$C" "$R"; printf '%s\n' "$out" | head -5 | sed 's/^/      /'; report "$code"

# ----------------------------------------------------------------------------
printf '\n%s=== RESUMO ===%s\n' "$B" "$R"
printf '  testes: %d\n' "$total"
if [ "$crashes" -eq 0 ]; then printf '  %s0 crashes/timeouts%s\n' "$G" "$R"
else printf '  %s%d crashes/timeouts%s\n' "$RD" "$crashes" "$R"; fi
printf '  Lê os "esperado" vs "obtido" acima: o script não decide sozinho o que está certo.\n'
