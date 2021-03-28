#pragma once
#include <iostream>
#include "values.hpp"
#include "../others/unit.hpp"

using std::cout;

unit_type* sum(unit_type* unit1, unit_type* unit2);
unit_type* dif(unit_type* unit1, unit_type* unit2);
unit_type* mul(unit_type* unit1, unit_type* unit2);
unit_type* divs(unit_type* unit1, unit_type* unit2);
unit_type* mod(unit_type* unit1, unit_type* unit2);

// WYRAZENIE
class AbstractExpression {
public:
    virtual void print() = 0;
    virtual unit_type* unit() = 0;
    virtual void init() = 0;
    virtual void flow_push(DependencyList* dep_list) = 0;
    virtual void flow_pop(DependencyList* dep_list) = 0;
};

// WYRAZENIE BINARNE
class BinaryExpression : public AbstractExpression{
public:
    AbstractValue* val_left;
    AbstractValue* val_right;
    BinaryExpression(AbstractValue* val_left, AbstractValue* val_right) : 
        val_left(val_left), val_right(val_right) {};
    void init() { val_left->init(); val_right->init(); }
    void flow_push(DependencyList* dep_list) { val_left->flow_push(dep_list); val_right->flow_push(dep_list); };
    void flow_pop(DependencyList* dep_list)  { val_right->flow_pop(dep_list); val_left->flow_pop(dep_list);   };
};

// WYRAZENIE UNARNE
class UnaryExpression : public AbstractExpression {
public:
    AbstractValue* val;
    UnaryExpression(AbstractValue* val) : val(val) {};
    void init() { val->init(); }
    void flow_push(DependencyList* dep_list) { val->flow_push(dep_list); };
    void flow_pop(DependencyList* dep_list)  { val->flow_pop(dep_list);  };
};

// DODAWANIE
class ExpressionSum : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    void print() { val_left->print(); cout << " + "; val_right->print(); }
    unit_type* unit() { return sum(val_left->unit(), val_right->unit()); }
};

// ODEJMOWANIE
class ExpressionDif : public BinaryExpression {
    using BinaryExpression::BinaryExpression;
    void print() { val_left->print(); cout << " - "; val_right->print(); }
    unit_type* unit() { return dif(val_left->unit(), val_right->unit()); }
};

// MNOZENIE
class ExpressionMul : public BinaryExpression {
    using BinaryExpression::BinaryExpression;
    void print() { val_left->print(); cout << " * "; val_right->print(); }
    unit_type* unit() { return mul(val_left->unit(), val_right->unit()); }
};

// DZIELENIE
class ExpressionDiv : public BinaryExpression {
    using BinaryExpression::BinaryExpression;
    void print() { val_left->print(); cout << " / "; val_right->print(); }
    unit_type* unit() { return divs(val_left->unit(), val_right->unit()); }
};

// RESZTA Z DZIELENIA
class ExpressionMod : public BinaryExpression {
    using BinaryExpression::BinaryExpression;
    void print() { val_left->print(); cout << " % "; val_right->print(); }
    unit_type* unit() { return mod(val_left->unit(), val_right->unit()); }
};

// WYRAZENIE PODSTAWOWE
class ExpressionBas : public UnaryExpression {
    using UnaryExpression::UnaryExpression;
    void print() { val->print(); }
    unit_type* unit() { return val->unit(); }
};