# pragma once
#include <math.h>
#include "code_generator.h"
#include "../symbol_table/data_manager.h"
#include "../others/types.h"
#include "../debugger/errors.h"
#include "../symbol_table/symbol_table.h"

extern int yylineno;
extern char* yytext;

int load_const(val_type val);
void put_variable(char* id);