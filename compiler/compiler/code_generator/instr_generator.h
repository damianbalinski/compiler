# pragma once
#include <stdbool.h>
#include "../others/types.h"
#include "../others/unit.h"
#include "../others/cond.h"

#define VALUE true
#define LOCATION false

#define INIT true
#define NOINIT false

#define FOR_TO true
#define FOR_DOWNTO false

void add_variable(char* id);
void add_array(char* id, input_type begin, input_type end);
void add_iterator(char* id);
void remove_iterator(char* id);
unit_type* get_iterator(char* id);

void for_cond(unit_type* unit1, unit_type* unit2, bool type);
void for_init(unit_type* unit1, unit_type* unit2);
void for_step(unit_type* unit1, unit_type* unit2, unit_type* unit3, bool type);
void for_free(cond_type* cond, unit_type* condition, unit_type* iterator, unit_type* value);

void jump_true_false(cond_type* cond, unit_type* condition, bool type);
void jump_end(cond_type* cond, unit_type* condition, bool type);
void jump_cond(cond_type* cond, unit_type* condition, bool type);
void jump_cmd(cond_type* cond, unit_type* condition, bool type);
void jumps_free(cond_type* cond, unit_type* condition);

unit_type* get_const(input_type val, bool type);
unit_type* get_variable(char* id, bool type, bool init);
unit_type* get_array_num(char* id, input_type num, bool type, bool init);
unit_type* get_array_var(char* id, char* id_var, bool type, bool init);

void assign(unit_type* unit1, unit_type* unit2);
void write(unit_type* unit);
void read(unit_type* unit);

unit_type* sum(unit_type* unit1, unit_type* unit2);
unit_type* dif(unit_type* unit1, unit_type* unit2);
unit_type* mul(unit_type* unit1, unit_type* unit2);

unit_type* eq_ne(unit_type* unit1, unit_type* unit2, bool type);
unit_type* lt_ge(unit_type* unit1, unit_type* unit2, bool type);
unit_type* gt_le(unit_type* unit1, unit_type* unit2, bool type);
