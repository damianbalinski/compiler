#pragma once
#include "types.h"
#include "stdbool.h"

#define EQUAL true
#define NOT_EQUAL false

#define LESS false
#define GREATER_EQUAL true

#define GREATER false
#define LESS_EQUAL true

typedef struct {
    int reg;
    input_type offset;
    bool type;
} unit_type;

unit_type* unit_alloc();
void unit_free(unit_type* unit);