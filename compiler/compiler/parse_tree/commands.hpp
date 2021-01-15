#pragma once
#include <string>
#include <vector>
#include "../symbol_table/symbol_table.hpp"
#include "../code_generator/registers_machine.hpp"
#include "../debugger/debugger.hpp"
#include "values.hpp"
#include "expressions.hpp"
#include "conditions.hpp"
#include "jumps.hpp"

// POJEDYNCZA KOMENDA
class AbstractCommand {
public:
    virtual void print() = 0;
    virtual void code() = 0;
    virtual void init() = 0;
};

// WEKTOR KOMEND
class CommandVector : public std::vector<AbstractCommand*> {
public:
    CommandVector() : std::vector<AbstractCommand*>() {};
    void print() { for (AbstractCommand* com: *this) com->print(); };
    void code()  { for (AbstractCommand* com: *this) com->code();  };
    void init()  { for (AbstractCommand* com: *this) com->init(); };
};

// KOMENDA ZLOZONA
class ConditionalCommand : public AbstractCommand {
public:
    AbstractCondition* cond;
    CommandVector* cmd_true;
    CommandVector* cmd_false;
    labels_type* labels;
    unit_type* cond_unit;
    ConditionalCommand(AbstractCondition* cond, CommandVector* cmd_true) :
        cond(cond), cmd_true(cmd_true), labels(new labels_type) {};
    ConditionalCommand(AbstractCondition* cond, CommandVector* cmd_true, CommandVector* cmd_false) :
        cond(cond), cmd_true(cmd_true), cmd_false(cmd_false), labels(new labels_type) {};
    void finish() { unit_free(cond_unit); }
    void init() { cond->init(); cmd_true->init(); };
};

// PETLA FOR
class ForCommand : public AbstractCommand {
public:
    char* iter_id;
    symbol* iter;
    CommandVector* cmd_true;
    labels_type* labels;
    unit_type* cond_unit;
    ForCommand(char* iter_id, CommandVector* cmd_true) :
        iter_id(iter_id), iter(add_iterator(iter_id)), cmd_true(cmd_true), labels(new labels_type) { 
            iter->is_visible = false; DBG_SYMBOL_PRINT(); };
    virtual void finish() { reg_free(cond_unit->reg), unit_free(cond_unit); };
    virtual void step() = 0;
};

// HALT
class CHalt : public AbstractCommand {
public:
    CHalt() {};
    void print();
    void code();
    void init() {};
};

// WRITE
class CWrite : public AbstractCommand {
public:
    AbstractValue* val;
    CWrite(AbstractValue* val) : val(val) {};
    void print();
    void code();
    void init() { val->init(); };
};

// READ
class CRead : public AbstractCommand {
public:
    AbstractValue* val;
    CRead(AbstractValue* val) : val(val) {};
    void print();
    void code();
    void init() { val->init(); };
};

// ASSIGN
class CAssign : public AbstractCommand {
public:
    AbstractValue* val;
    AbstractExpression* exp;
    CAssign(AbstractValue* val, AbstractExpression* exp) :
        val(val), exp(exp) {};
    void print();
    void code();
    void init() { val->init(); exp->init(); };
};

// IF THEN
class CIfThen : public ConditionalCommand {
public:
    CIfThen(AbstractCondition* cond, CommandVector* cmd_true) :
        ConditionalCommand(cond, cmd_true) {};
    void print();
    void code();
};

// IF THEN ELSE
class CIfThenElse : public ConditionalCommand {
public:
    CIfThenElse(AbstractCondition* cond, CommandVector* cmd_true, CommandVector* cmd_false) :
        ConditionalCommand(cond, cmd_true, cmd_false) {};
    void print();
    void code();
    void init() { cond->init(); cmd_true->init(); cmd_false->init(); };
};

// WHILE
class CWhile : public ConditionalCommand {
public:
    CWhile(AbstractCondition* cond, CommandVector* cmd_true) :
        ConditionalCommand(cond, cmd_true) {};
    void print();
    void code();
};

// REPEAT
class CRepeat : public ConditionalCommand {
public:
    CRepeat(AbstractCondition* cond, CommandVector* cmd_true) :
        ConditionalCommand(cond, cmd_true) {};
    void print();
    void code();
};

// FOR TO
class CForTo : public ForCommand {
public:
    AbstractCondition* cond;
    CForTo(char* iter_id, AbstractValue* val1, AbstractValue* val2, CommandVector* cmd_true) :
        ForCommand(iter_id, cmd_true), 
       cond(new ConditionForTo(val1, val2, iter)) {};
    void step();
    void print();
    void code();
    void init() { cond->init(); iter->is_visible = true; cmd_true->init(); iter->is_visible = false; };
};

// FOR DOWNTO
class CForDownto : public ForCommand {
public:
    AbstractCondition* cond;
    CForDownto(char* iter_id, AbstractValue* val1, AbstractValue* val2, CommandVector* cmd_true) :
        ForCommand(iter_id, cmd_true), 
       cond(new ConditionForDownto(val1, val2, iter)) {};
    void step();
    void print();
    void code();
    void init() { cond->init(); iter->is_visible = true; cmd_true->init(); iter->is_visible = false; };
};