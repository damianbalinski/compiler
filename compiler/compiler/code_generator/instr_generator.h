# pragma once
#include <stdbool.h>
#include "../others/types.h"
#include "../others/unit.h"

#define VALUE true
#define LOCATION false
#define INIT true
#define NOINIT false

void add_variable(char* id);                                    // DONE
void add_array(char* id, input_type begin, input_type end);     // DONE

unit_type* get_const(input_type val, bool type);
unit_type* get_variable(char* id, bool type, bool init);
unit_type* get_array_num(char* id, input_type num, bool type, bool init);
unit_type* get_array_var(char* id, char* id_var, bool type, bool init);

void assign(unit_type* unit1, unit_type* unit2);
void write(unit_type* unit);
void read(unit_type* unit);