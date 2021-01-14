# pragma once
#include "../others/types.hpp"
#include "../others/unit.hpp"
#include "../symbol_table/symbol_table.hpp"

#define VALUE true
#define LOCATION false

#define INIT true
#define NOINIT false

#define FOR_TO true
#define FOR_DOWNTO false

#define IF_THEN true
#define IF_THEN_ELSE false

void add_variable(char* id);
void add_array(char* id, data_type begin, data_type end);
void remove_iterator(char* id);
symbol* add_iterator(char* id);

unit_type* for_init(symbol* iter, unit_type* begin, unit_type* end, bool type);
void for_step(symbol* iter, unit_type* condition, bool type);
void for_free(unit_type* condition);

unit_type* get_const(input_type val, bool type);
unit_type* get_variable(char* id, bool type, bool init);
unit_type* get_array_num(char* id, input_type num, bool type, bool init);
unit_type* get_array_var(char* id, char* id_var, bool type, bool init);

unit_type* sum(unit_type* unit1, unit_type* unit2);
unit_type* dif(unit_type* unit1, unit_type* unit2);
unit_type* mul(unit_type* unit1, unit_type* unit2);
unit_type* divs(unit_type* unit1, unit_type* unit2);
unit_type* mod(unit_type* unit1, unit_type* unit2);

unit_type* eq_ne(unit_type* unit1, unit_type* unit2, bool type);
unit_type* lt_ge(unit_type* unit1, unit_type* unit2, bool type);
unit_type* gt_le(unit_type* unit1, unit_type* unit2, bool type);
