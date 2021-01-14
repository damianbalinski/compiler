#pragma once
#include <iostream>
#include <cln/cln.h>
#include "../others/types.hpp"
#include "../others/unit.hpp"
#include "../symbol_table/symbol_table.hpp"

using std::cout;

#define VALUE true
#define LOCATION false

#define INIT true
#define NOINIT false

void add_variable(char* id);
void add_array(char* id, data_type begin, data_type end);
symbol* add_iterator(char* id);

unit_type* get_const(input_type val, bool type);
unit_type* get_variable(symbol* sym, bool type, bool init);
unit_type* get_array_num(symbol* sym, input_type num, bool type, bool init);
unit_type* get_array_var(char* id, char* id_var, bool type, bool init);

class AbstractValue {
public:
    bool type;
    bool init;
    AbstractValue(bool type, bool init) : 
        type(type), init(init) {};
    virtual void print() = 0;
    virtual unit_type* unit() = 0;
    virtual void flow() {};
};

// LICZBA
class VNum : public AbstractValue {
public:
    cln::cl_I val;
    VNum(data_type val, bool type) :
        AbstractValue(type, true), val(val) {};
    void print() { cout << val; };
    unit_type* unit() { return get_const(val, type); }
    void flow() {};
};

// ZMIENNA
class VVar : public AbstractValue {
public:
    char* var_id;
    symbol* var;
    VVar(char* var_id, bool type, bool init) :
        AbstractValue(type, init), var_id(var_id) {};
    void print() { cout << var_id; }
    unit_type* unit() { return get_variable(var, type, init); }
    void flow();
};

// TABLICA INDEKSOWANA LICZBA
class VArrNum : public AbstractValue {
public:
    char* arr_id;
    symbol* arr;
    cln::cl_I val;
    VArrNum(char* arr_id, data_type val, bool type, bool init) : 
        AbstractValue(type, init), arr_id(arr_id), val(val) {};
    void print() { cout << arr_id << "[" << val << "]"; }
    unit_type* unit() { return get_array_num(arr, val, type, init); }
    void flow();
};

// TABLICA INDEKSOWANA ZMIENNA
class VArrVar : public AbstractValue {
public:
    char* id_arr;
    char* id_var;
    VArrVar(char* id_arr, char* id_var, bool type, bool init) :
        AbstractValue(type, init), id_arr(id_arr), id_var(id_var) {};
    void print() { cout << id_arr << "[" << id_var << "]"; }
    unit_type* unit() { return get_array_var(id_arr, id_var, type, init); }
};
