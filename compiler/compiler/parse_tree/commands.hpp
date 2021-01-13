#pragma once
#include <string>
#include <vector>

using std::string;

class AbstractCommand {
public:
    string name;

    AbstractCommand(string name) : name(name){};
    AbstractCommand() {};
    virtual void print_raw() = 0;
};


class CommandVector : public std::vector<AbstractCommand*> {
public:
    CommandVector() : std::vector<AbstractCommand*>() {};
    void print_raw();
};

// WRITE COMMAND
class CWrite : public AbstractCommand {
public:
    void print_raw();
};

// READ COMMAND
class CRead : public AbstractCommand {
public:
    void print_raw();
};

// ASSIGN COMMAND
class CAssign : public AbstractCommand {
public:
    void print_raw();
};

// IF ELSE COMMAND
class CIfThen : public AbstractCommand {
public:
    CommandVector* cmd_true;
    CIfThen(CommandVector* cmd_true) : cmd_true(cmd_true) {};
    void print_raw();
};

// WHILE COMMAND
class CWhile : public AbstractCommand {
public:
    CommandVector* cmd_true;
    CWhile(CommandVector* cmd_true) : cmd_true(cmd_true) {};
    void print_raw();
};

// REPEAT COMMAND
class CRepeat : public AbstractCommand {
public:
    CommandVector* cmd_true;
    CRepeat(CommandVector* cmd_true) : cmd_true(cmd_true) {};
    void print_raw();
};

// FOR_TO COMMAND
class CForTo : public AbstractCommand {
public:
    CommandVector* cmd_true;
    CForTo(CommandVector* cmd_true) : cmd_true(cmd_true) {};
    void print_raw();
};

// FOR_DOWNTO COMMAND
class CForDownto : public AbstractCommand {
public:
    CommandVector* cmd_true;
    CForDownto(CommandVector* cmd_true) : cmd_true(cmd_true) {};
    void print_raw();
};