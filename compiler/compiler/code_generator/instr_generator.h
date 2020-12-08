# pragma once
#include <stdbool.h>
#include "../others/types.h"
#include "../others/unit.h"
#define LVARIABLE true
#define RVARIABLE false

unit_type* get_const(input_type val);                   // DONE
unit_type* get_variable(char* id, bool type);           // DONE
unit_type* get_larray_num(char* id, input_type num);    // DONE
unit_type* get_larray_var(char* id, char* id_var);      // DONE

unit_type get_rvariable(char* id);

void add_variable(char* id);
void add_array(char* id, input_type begin, input_type end);

