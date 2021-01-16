AUTOR
Damian Balinski | 250332

NARZĘDZIA
g++ 9.3.0
bison 3.7.3
flex 2.6.4
GNU Make 4.2.1
libcln-dev 1.3.6

INSTALOWANIE
sudo apt-get install libcln-dev     # biblioteka cln
make                                # kompilacja projektu
make clean                          # sprzatanie smieci

OPIS PLIKOW
code_generator/code_generator.cpp   - generator kodow maszynowych
code_generator/register_machine.cpp - funkcje obslugujace rejestry, generujace podstawowe instrukcje
debugger/colors.hpp           - kolory
debugger/debugger.hpp         - makra do debugowania
debugger/errors.hpp           - bledy
debugger/warnings.hpp         - ostrzezenia
optimizer/optimizer.hpp       - makra do wlaczania/wylaczania optymalizacji
others/const.hpp              - stale cln
others/types.hpp              - typy
others/unit.cpp               - struktura z rejestrem/wartoscia/offsetem uzywana podczas generowania kodu
parse_table/commands.cpp      - klasy komend
parse_table/conditions.cpp    - klasy warunkow
parse_table/expressions.cpp   - klasy wyrazen
parse_table/values.cpp        - klasy wartosci
parse_table/jumps.cpp         - funkcje pomocnicze do skokow
symbol_table/data_manager.cpp - alokator pamieci
symbol_table/symbol_table.cpp - tablica symboli
lexer.l                       - lekser
parser.y                      - parser, funkcja startowa
