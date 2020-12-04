# pragma once
#include <math.h>
#include "code_generator.h"
#include "../symbol_table/data_manager.h"
#include "../others/types.h"
#include "../debugger/errors.h"
#include "../symbol_table/symbol_table.h"

extern int yylineno;
extern char* yytext;

int get_const(val_type val);
int get_variable(char* id);     // TODO
int get_table(char* id);        // TODO

void put_variable(char* id);
void put_table(char* id);       // TODO

int reg_add(int x, int y);