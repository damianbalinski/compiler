#pragma once
#include <iostream>
#include <cln/cln.h>
#include "../others/types.hpp"
#include "../others/unit.hpp"
#include "../symbol_table/symbol_table.hpp"

using std::cout;
using std::endl;

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
unit_type* get_array_var(symbol* sym, symbol* sym_var, bool type, bool init);

class AbstractValue {
public:
    bool type;
    bool is_init;
    AbstractValue(bool type, bool is_init) : 
        type(type), is_init(is_init) {};
    virtual void print() = 0;
    virtual unit_type* unit() = 0;
    virtual void init() = 0;
    virtual void flow_push(DependencyList* dep_list) = 0;
    virtual void flow_pop(DependencyList* dep_list) = 0;
    virtual void flow_add(int prior, DependencyList* dep_list) = 0;
    virtual bool clean() = 0;
};

// LICZBA
class VNum : public AbstractValue {
public:
    cln::cl_I val;
    char* val_id;
    symbol* val_sym;
    VNum(data_type val, char* val_id, bool type) :
        AbstractValue(type, true), val(val), val_id(val_id) {};
    void print() { cout << val_id; };
    unit_type* unit() { return get_const(val, type); }
    void init();
    void flow_push(DependencyList* dep_list) { dep_list->push_back(val_sym); };
    void flow_pop(DependencyList* dep_list)  { dep_list->pop_back();         };
    void flow_add(int prior, DependencyList* dep_list)  { val_sym->prior = maxi(val_sym->prior, prior); val_sym->deps->add(dep_list); };
    bool clean() { return false; };
};

// ZMIENNA
class VVar : public AbstractValue {
public:
    char* var_id;
    symbol* var;
    VVar(char* var_id, bool type, bool is_init) :
        AbstractValue(type, is_init), var_id(var_id) {};
    void print() { cout << var_id; }
    unit_type* unit() { return get_variable(var, type, is_init); }
    void init();
    void flow_push(DependencyList* dep_list) { dep_list->push_back(var); };
    void flow_pop(DependencyList* dep_list)  { dep_list->pop_back();     };
    void flow_add(int prior, DependencyList* dep_list)  { var->prior = maxi(var->prior, prior); var->deps->add(dep_list); };
    bool clean() { return (var->prior == PWHITE) ? true : false; };
};

// TABLICA INDEKSOWANA LICZBA
class VArrNum : public AbstractValue {
public:
    char* arr_id;
    symbol* arr;
    cln::cl_I val;
    VArrNum(char* arr_id, data_type val, bool type, bool is_init) : 
        AbstractValue(type, is_init), arr_id(arr_id), val(val) {};
    void print() { cout << arr_id << "[" << val << "]"; }
    unit_type* unit() { return get_array_num(arr, val, type, is_init); }
    void init();
    void flow_push(DependencyList* dep_list) { dep_list->push_back(arr); };
    void flow_pop(DependencyList* dep_list)  { dep_list->pop_back();     };
    void flow_add(int prior, DependencyList* dep_list)  { arr->prior = maxi(arr->prior, prior); arr->deps->add(dep_list); };
    bool clean() { return (arr->prior == PWHITE) ? true : false; };
};

// TABLICA INDEKSOWANA ZMIENNA
class VArrVar : public AbstractValue {
public:
    char* arr_id;
    char* var_id;
    symbol* arr;
    symbol* var;
    VArrVar(char* arr_id, char* var_id, bool type, bool is_init) :
        AbstractValue(type, is_init), arr_id(arr_id), var_id(var_id) {};
    void print() { cout << arr_id << "[" << var_id << "]"; }
    unit_type* unit() { return get_array_var(arr, var, type, is_init); }
    void init();
    void flow_push(DependencyList* dep_list) { dep_list->push_back(arr); dep_list->push_back(var); arr->deps->add(var); };
    void flow_pop(DependencyList* dep_list)  { dep_list->pop_back();     dep_list->pop_back();     };
    void flow_add(int prior, DependencyList* dep_list)  { arr->prior = maxi(arr->prior, prior); var->prior = maxi(var->prior, prior);  
    arr->deps->add(dep_list); arr->deps->add(var); };
    bool clean() { return (arr->prior == PWHITE) ? true : false; };
};
