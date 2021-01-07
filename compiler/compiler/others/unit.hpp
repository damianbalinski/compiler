#pragma once
#include "types.hpp"

#define EQUAL true
#define NOT_EQUAL false

#define LESS false
#define GREATER_EQUAL true

#define GREATER false
#define LESS_EQUAL true

typedef struct {
    int reg;
    int reg_prev;
    input_type offset;
    bool type;
} unit_type;

unit_type* unit_alloc();
void unit_free(unit_type* unit);