# pragma once
#include <stdbool.h>
#include "../others/types.h"
#include "../others/unit.h"
#define LVARIABLE true
#define RVARIABLE false

void add_variable(char* id);                                    // DONE
void add_array(char* id, input_type begin, input_type end);     // DONE

unit_type* get_const(input_type val);                           // DONE
unit_type* get_variable(char* id, bool type);                   // DONE
unit_type* get_array_num(char* id, input_type num, bool type);  // DONE
unit_type* get_array_var(char* id, char* id_var, bool type);    // DONE
