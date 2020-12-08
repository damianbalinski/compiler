#pragma once
#include "types.h"

typedef struct {
    int reg;
    input_type offset;
} unit_type;

unit_type* unit_alloc();
void unit_free(unit_type* unit);