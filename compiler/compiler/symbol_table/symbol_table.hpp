# pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <cln/integer.h>
#include "../others/types.hpp"

#define VARIABLE true
#define ARRAY false

#define PWHITE 0
#define PRED 1
#define PBLACK 2

using std::vector;
using std::cout;
using std::endl;

class DependencyList;

typedef struct symbol
{
    char* id;               /* id symbolu                */
    bool type;              /* zmianna/tablica           */
    bool is_init;           /* czy zainicjalizowana      */
    bool is_const;          /* czy stala                 */
    bool is_visible;        /* czy widoczna              */
    input_type offset;      /* lokalizacja w pamieci     */
    input_type begin;       /* indeks poczatkowy tablicy */
    input_type end;         /* indeks poczatkowy tablicy */
    struct symbol* next;    /* nastepny symbol           */
    DependencyList* deps;   /* lista zaleznosci          */
    int prior;              /* priorytet                 */
    //cln::cl_I val;        /* wartosc                   */
    
} symbol;

class DependencyList : public vector<symbol*> {
public:
    DependencyList() : vector<symbol*>() {};
    DependencyList(symbol* sym) : vector<symbol*>(1, sym) {};
    void print() { for(symbol* sym : *this) cout << sym->id << " "; cout << endl; };
    void add(DependencyList* deps) { for(symbol* sym: *deps) add(sym); }
    void add(symbol* sym) { if (std::find(begin(), end(), sym) == end()) push_back(sym); }   
};

symbol* sym_put(char *id);
symbol* sym_get(char*id);
void sym_print();
void deps_print();
