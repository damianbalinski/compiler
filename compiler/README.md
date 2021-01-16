# Kompilator

## Spis treści

* [O projekcie](#o-projekcie)
* [Narzędzia](#narzędzia)
* [Instalacja](#instalacja)
* [Optymalizacje](#optymalizacje)
* [Debugowanie](#debugowanie)

### O projekcie
Kompilator jest projektem zaliczeniowym do kursu *"Języki formalne i techniki translacji"* podczas V semestru Informatyki WPPT na PWr. Projekt Wykonał Damian Baliński.


### Narzędzia

* g++ 9.3.0
* bison 3.7.3
* flex 2.6.4
* GNU Make 4.2.1
* libcln-dev 1.3.6


### Instalacja
Instalowanie dodatkowych bibliotek
```sh
sudo apt-get install libcln-dev
```

Kompilowanie projektu
```sh
make
make clean
```

Uruchamianie kompilatora
```
./temp <src> <dest>
```

### Optymalizacje

- [X] OPTIMIZE_SUM
- - [X] OPTIMIZE_SUM_BOTH
- - [X] OPTIMIZE_SUM_LEFT  
- - [X] OPTIMIZE_SUM_RIGHT  
- - [X] OPTIMIZE_SUM_EQUAL  
  

- [X] OPTIMIZE_DIF
- - [X] OPTIMIZE_DIF_BOTH
- - [X] OPTIMIZE_DIF_LEFT
- - [X] OPTIMIZE_DIF_RIGHT
- - [X] OPTIMIZE_DIF_EQUAL


- [X] OPTIMIZE_MUL
- - [X] OPTIMIZE_MUL_BOTH
- - [X] OPTIMIZE_MUL_LEFT
- - [X] OPTIMIZE_MUL_LEFT_ZERO
- - [X] OPTIMIZE_MUL_LEFT_TWO_POWER
- - [X] OPTIMIZE_MUL_LEFT_OTHERS
- - [X] OPTIMIZE_MUL_RIGHT
- - [X] OPTIMIZE_MUL_RIGHT_ZERO
- - [X] OPTIMIZE_MUL_RIGHT_TWO_POWER
- - [X] OPTIMIZE_MUL_RIGHT_OTHERS


- [X] OPTIMIZE_DIV
- - [X] OPTIMIZE_DIV_BOTH
- - [X] OPTIMIZE_DIV_LEFT
- - [X] OPTIMIZE_DIV_RIGHT
- - [X] OPTIMIZE_DIV_RIGHT_ZERO
- - [X] OPTIMIZE_DIV_RIGHT_TWO_POWER
- - [X] OPTIMIZE_DIV_EQUAL


- [X] OPTIMIZE_MOD
- - [X] OPTIMIZE_MOD_BOTH
- - [X] OPTIMIZE_MOD_LEFT
- - [X] OPTIMIZE_MOD_RIGHT
- - [X] OPTIMIZE_MOD_RIGHT_SIMPLE
- - [X] OPTIMIZE_MOD_RIGHT_TWO_POWER
- - [X] OPTIMIZE_MOD_EQUAL


- [X] OPTIMIZE_CONDITIONS
- - [X] OPTIMIZE_LT_GE
- - [X] OPTIMIZE_GT_LE
- - [X] OPTIMIZE_EQ_NE_BOTH
- - [X] OPTIMIZE_EQ_NE_LEFT
- - [X] OPTIMIZE_EQ_NE_LEFT_ZERO
- - [X] OPTIMIZE_EQ_NE_RIGHT
- - [X] OPTIMIZE_EQ_NE_RIGHT_ZERO


- [X] OPTIMIZE_POSTPONE
- - [X] OPTIMIZE_CONST_POSTPONE
- - [X] OPTIMIZE_VAR_POSTPONE
- - [X] POTIMIZE_ARR_NUM_POSTPONE
