#pragma once
#include <iostream>
#include "values.hpp"
#include "../code_generator/instr_generator.hpp"

using std::cout;

class AbstractCondition {
public:
    AbstractValue* val_left;
    AbstractValue* val_right;
    AbstractCondition(AbstractValue* val_left, AbstractValue* val_right) : 
        val_left(val_left), val_right(val_right) {};
    virtual void print() = 0;
    virtual unit_type* unit() = 0;
};

class ConditionLT : public AbstractCondition {
public:
    using AbstractCondition::AbstractCondition;
    void print() { val_left->print(); cout << " < "; val_right->print(); };
    unit_type* unit() { return lt_ge(val_left->unit(), val_right->unit(), LESS); }
};

class ConditionLE : public AbstractCondition {
public:
    using AbstractCondition::AbstractCondition;
    void print() { val_left->print(); cout << " <= "; val_right->print(); };
    unit_type* unit() { return gt_le(val_left->unit(), val_right->unit(), LESS_EQUAL); }
};

class ConditionGT : public AbstractCondition {
public:
    using AbstractCondition::AbstractCondition;
    void print() { val_left->print(); cout << " > "; val_right->print(); };
    unit_type* unit() { return gt_le(val_left->unit(), val_right->unit(), GREATER); }
};

class ConditionGE : public AbstractCondition {
public:
    using AbstractCondition::AbstractCondition;
    void print() { val_left->print(); cout << " >= "; val_right->print(); };
    unit_type* unit() { return lt_ge(val_left->unit(), val_right->unit(), GREATER_EQUAL); }
};

class ConditionEQ : public AbstractCondition {
public:
    using AbstractCondition::AbstractCondition;
    void print() { val_left->print(); cout << " = "; val_right->print(); };
    unit_type* unit() { return eq_ne(val_left->unit(), val_right->unit(), EQUAL); }
};

class ConditionNE : public AbstractCondition {
public:
    using AbstractCondition::AbstractCondition;
    void print() { val_left->print(); cout << " != "; val_right->print(); };
    unit_type* unit() { return eq_ne(val_left->unit(), val_right->unit(), NOT_EQUAL); }
};