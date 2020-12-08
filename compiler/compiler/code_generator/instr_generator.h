# pragma once
#include "../others/types.h"
#include "../others/unit.h"

unit_type* get_const(input_type val);
unit_type get_lvariable(char* id);
unit_type get_larray_num(char* id, input_type val);
unit_type get_larray_var(char* id, char* id_var);
unit_type get_rvariable(char* id);

void add_variable(char* id);
void add_array(char* id, input_type begin, input_type end);
