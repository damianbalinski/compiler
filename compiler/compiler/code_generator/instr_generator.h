# pragma once
#include "code_generator.h"
#include "instr_reg.h"
#include "../symbol_table/data_manager.h"
#include "../others/types.h"
#include "../debugger/errors.h"
#include "../symbol_table/symbol_table.h"

extern int yylineno;
extern char* yytext;

unit_type get_const(input_type val);                    // DONE
unit_type get_lvariable(char* id);                      // DONE
unit_type get_larray_num(char* id, input_type val);     // DONE
unit_type get_larray_var(char* id, char* id_var);       // PEND
unit_type get_rvariable(char* id);                      // DONE


void add_variable(char* id);                                    // DONE
void add_array(char* id, input_type begin, input_type end);     // DONE
