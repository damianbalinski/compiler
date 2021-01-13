#pragma once
#include <cln/integer.h>
#include <iostream>
#include <cln/cln.h>
#include "../others/types.hpp"
#include "../others/unit.hpp"
#include "../code_generator/instr_generator.hpp"

using std::cout;

class AbstractValue {
public:
    bool type;
    bool init;
    AbstractValue(bool type, bool init) : 
        type(type), init(init) {};
    virtual void print() = 0;
    virtual unit_type* unit() = 0;
};

// LICZBA
class VNum : public AbstractValue {
public:
    cln::cl_I val;
    VNum(data_type val, bool type) :
        AbstractValue(type, true), val(val) {};
    void print() { cout << val; };
    unit_type* unit() { return get_const(val, type); }
};

// ZMIENNA
class VVar : public AbstractValue {
public:
    char* id_var;
    VVar(char* id_var, bool type, bool init) :
        AbstractValue(type, init), id_var(id_var) {};
    void print() { cout << id_var; }
    unit_type* unit() { return get_variable(id_var, type, init); }
};

// TABLICA INDEKSOWANA LICZBA
class VArrNum : public AbstractValue {
public:
    char* id_arr;
    cln::cl_I val;
    VArrNum(char* id_arr, data_type val, bool type, bool init) : 
        AbstractValue(type, init), id_arr(id_arr), val(val) {};
    void print() { cout << id_arr << "[" << val << "]"; }
    unit_type* unit() { return get_array_num(id_arr, val, type, init); }
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
