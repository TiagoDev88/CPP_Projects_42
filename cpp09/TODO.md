# CPP09: o que falta tratar

Lista feita a partir da revisão do código e dos testes em [tests/](tests/).
Marca com `[x]` à medida que fores resolvendo.

**Legenda:** 🔴 pode chumbar · 🟡 convém corrigir · 🟢 opcional / decisão tua

---

## Como correr os testes

```bash
cd cpp09
./tests/test_ex00.sh          # testa o teu ex00
./tests/test_ex01.sh          # testa o teu ex01
./tests/test_ex02.sh          # testa o teu ex02

./tests/test_ex01.sh /caminho/para/ex01   # testa o projeto de OUTRA pessoa
```

Cada script corre `make re`, verifica se o Makefile usa as flags e corre todos os casos.
Para cada caso mostra o comando, o **esperado**, o **obtido** e o exit code.
Crashes (💥) e programas presos (⏱) aparecem a vermelho.

- **ex00 e ex01:** lê o "esperado" e o "obtido". Em alguns casos há mais do que uma resposta aceitável.
- **ex02:** a ordenação é verificada automaticamente (✅/❌) contra o `sort -n`.

---

## ex00: btc

### Já feito
- [x] Includes que faltavam (`<string>`, `<cstdlib>`, `<stdexcept>`, `<cctype>`). Sem o `<cstdlib>` não compilava com `-std=c++98`.
- [x] Makefile com `-Wall -Wextra -Werror -std=c++98` descomentado.

### Por fazer
- [ ] 🟡 **Sem argumento, a mensagem não é a do subject.**
  O subject mostra `./btc` → `Error: could not open file.`
  Hoje dá `Error: Please put one file an argument`. Está em [main.cpp](ex00/src/main.cpp).
- [ ] 🟡 **Exit codes errados.**
  - Sem argumento devolve `-1` (o shell mostra 255).
  - Quando há erro (ficheiro não abre) devolve `0`.
  - Usar `return 1` nos dois casos.
- [ ] 🟡 **`nan` é aceite como valor.**
  `2011-01-03 | nan` dá `2011-01-03 => nan = nan`. Devia ser `Error: bad input`.
  Dica: `value != value` só é verdade para NaN.
- [ ] 🟡 **Uma pasta como argumento não dá erro.**
  `./btc /tmp` imprime uma linha vazia e sai com 0. O `ifstream` "abre" pastas no Linux, mas o `getline` falha logo.
  Dica: se o primeiro `getline` (o do header) falhar, tratar como erro.
- [ ] 🟡 **Espaço depois do valor dá `bad input`.**
  `2011-01-03 | 3 ` (com espaço invisível no fim) é rejeitado. Há avaliadores que testam isto.
- [ ] 🟢 **`-0` mostra `2011-01-03 => -0 = -0`.** Fica estranho. Tratar como 0 ou como `not a positive number`.
- [ ] 🟢 **Dois argumentos:** `./btc input.txt outro` ignora o segundo sem aviso. O subject diz "a file".
- [ ] 🟢 **`0x10` é aceite como 16** (o `strtod` lê hexadecimal). `1e3` também é aceite como 1000.
- [ ] 🟢 **Fim de linha Windows (`\r\n`):** todas as linhas dão `bad input`. É aceitável, mas sabe explicar porquê.
- [ ] 🟢 **Header não é validado:** a primeira linha é sempre saltada, seja ela qual for.

---

## ex01: RPN

- [ ] 🔴 **Divisão por zero faz CRASH (SIGFPE).**
  `./RPN "1 0 /"`, `"0 0 /"` e `"5 3 3 - /"` rebentam o programa.
  Está no `case '/'` de [RPN.cpp](ex01/src/RPN.cpp): falta verificar `right == 0` antes de dividir.
- [ ] 🟡 **Overflow dá resultados errados.**
  `"9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"` (9¹⁰) dá lixo em vez de erro.
  Dica: fazer as contas em `long` e lançar erro se passar de `INT_MAX` / `INT_MIN`.
- [ ] 🟡 **Exit codes errados.**
  - Quando dá `Error`, o programa sai com `0`. Devia ser `1` (no `catch` do [main.cpp](ex01/src/main.cpp)).
  - Com argumentos errados devolve `-1`. Usar `1`.
- [ ] 🟡 **Includes em falta** no [RPN.hpp](ex01/inc/RPN.hpp): `<string>`, `<stdexcept>` (para o `std::runtime_error`) e `<cctype>` (para o `std::isdigit`). Hoje compila por acaso, porque outros headers os incluem.
- [ ] 🟢 **Mensagem sem argumentos:** o subject só mostra `Error`. A tua frase longa também é aceitável.
- [ ] 🟢 `isOperator(char &c)` → `isOperator(char c)`. Não altera o caractere, por isso não precisa de referência.

---

## ex02: PmergeMe

Todos os testes de ordenação passam (incluindo 3000 e 10000 números e 100 sequências aleatórias), e não há crashes.

- [ ] 🟡 **Template vs uma função por contentor.**
  O subject diz *"strongly advised to implement your algorithm for each container and thus to avoid using a generic function"*.
  Decide: ou fazes duas funções, ou preparas a justificação ("o template gera uma versão por contentor, por isso os tempos são reais").
- [ ] 🟢 **Apagar o bloco comentado** do `sortVector` antigo, no fim do [PmergeMe.cpp](ex02/src/PmergeMe.cpp).
- [ ] 🟢 **Comentários:** `odd or pair` → `odd or even`, e `retire` → `remove`.
- [ ] 🟢 **Precisão do tempo:** `std::fixed << std::setprecision(5)` para ficar `36.00000 us`.
- [ ] 🟢 **Decisões a saber justificar:**
  - `0` é rejeitado (não é positivo).
  - `"3 5 9"` num só argumento é rejeitado (cada argumento é um número).
  - `"   9"` é rejeitado (só dígitos).
  - `00042` é aceite como 42.
- [ ] 🟢 (opcional) Dividir o `sortInput` em funções mais pequenas (`makePairs`, `buildLows`, `insertLows`).

---

## Geral (vale para todos)

- [ ] O executável não deve ir para o git. Acrescenta ao `.gitignore`:
  ```
  cpp09/ex00/btc
  cpp09/ex01/RPN
  cpp09/ex02/PmergeMe
  .build/
  ```
- [ ] Só entregar os ficheiros pedidos (Makefile, main.cpp, X.cpp, X.hpp). O ex00 precisa também do `data.csv`.
- [ ] Contentores: `std::map` (ex00), `std::stack` (ex01), `std::vector` + `std::deque` (ex02). Nenhum se repete ✅

---

## O que verificar quando avaliares outra pessoa

Os scripts testam quase tudo. Isto é o que deves ver à mão:

| o quê | como |
|---|---|
| flags no Makefile | `-Wall -Wextra -Werror -std=c++98` não comentadas |
| Forma Canónica Ortodoxa | construtor por defeito, de cópia, `operator=` e destrutor em cada classe |
| contentores repetidos | o ex01 não pode usar o contentor do ex00; o ex02 não pode usar os do ex00 nem os do ex01 |
| erros no stderr | `./programa <input mau> 2>/dev/null` não deve mostrar nada |
| leaks | `valgrind --leak-check=full ./programa ...` |
| ex02 é mesmo Ford-Johnson | procurar pares, recursão nos maiores, Jacobsthal e pesquisa binária (não um `std::sort` escondido) |
| ex02 usa 2 contentores a sério | os dois são ordenados, não é um copiado do outro depois de ordenado |
