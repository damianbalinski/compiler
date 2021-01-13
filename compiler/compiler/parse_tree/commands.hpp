#pragma once
#include <string>
#include <vector>
#include "values.hpp"
#include "expressions.hpp"
#include "conditions.hpp"

using std::string;

// POJEDYNCZA KOMENDA
class AbstractCommand {
public:
    string name;

    AbstractCommand(string name) : name(name){};
    AbstractCommand() {};
    virtual void print() = 0;
    virtual void code() { cout << "code not yet implemented"; };
};

// WEKTOR KOMEND
class CommandVector : public std::vector<AbstractCommand*> {
public:
    CommandVector() : std::vector<AbstractCommand*>() {};
    void print() { for (AbstractCommand* com: *this) com->print(); };
    void code()  { for (AbstractCommand* com: *this) com->code();  };
};

// HALT
class CHalt : public AbstractCommand {
public:
    CHalt() {};
    void print();
    void code();
};

// WRITE
class CWrite : public AbstractCommand {
public:
    AbstractValue* val;
    CWrite(AbstractValue* val) : val(val) {};
    void print();
    void code();
};

// READ
class CRead : public AbstractCommand {
public:
    AbstractValue* val;
    CRead(AbstractValue* val) : val(val) {};
    void print();
    void code();
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
};

// IF ELSE COMMAND
class CIfThen : public AbstractCommand {
public:
    AbstractCondition* con;
    CommandVector* cmd_true;
    CIfThen(AbstractCondition* con, CommandVector* cmd_true) :
        con(con), cmd_true(cmd_true) {};
    void print();
    using AbstractCommand::code;
};

// IF THEN ELSE COMMAND
class CIfThenElse : public AbstractCommand {
public:
    AbstractCondition* con;
    CommandVector* cmd_true;
    CommandVector* cmd_false;
    CIfThenElse(AbstractCondition* con, CommandVector* cmd_true, CommandVector* cmd_false) :
        con(con), cmd_true(cmd_true), cmd_false(cmd_false) {};
    void print();
    using AbstractCommand::code;
};

// WHILE
class CWhile : public AbstractCommand {
public:
    AbstractCondition* con;
    CommandVector* cmd_true;
    cond_type* cond;
    unit_type* cond_unit;

    CWhile(AbstractCondition* con, CommandVector* cmd_true) :
        con(con), cmd_true(cmd_true) {};
    void print();
    void code();
};

// REPEAT COMMAND
class CRepeat : public AbstractCommand {
public:
    AbstractCondition* con;
    CommandVector* cmd_true;
    CRepeat(AbstractCondition* con, CommandVector* cmd_true) :
        con(con), cmd_true(cmd_true) {};
    void print();
    using AbstractCommand::code;
};

// FOR_TO COMMAND
class CForTo : public AbstractCommand {
public:
    const char* iter;
    AbstractValue* val1;
    AbstractValue* val2;
    CommandVector* cmd_true;
    CForTo(const char* iter, AbstractValue* val1, AbstractValue* val2, CommandVector* cmd_true) :
        iter(iter), val1(val1), val2(val2), cmd_true(cmd_true) {};
    void print();
    using AbstractCommand::code;
};

// FOR_DOWNTO COMMAND
class CForDownto : public AbstractCommand {
public:
    const char* iter;
    AbstractValue* val1;
    AbstractValue* val2;
    CommandVector* cmd_true;
    CForDownto(const char* iter, AbstractValue* val1, AbstractValue* val2, CommandVector* cmd_true) :
        iter(iter), val1(val1), val2(val2), cmd_true(cmd_true) {};
    void print();
    using AbstractCommand::code;
};