#include "../debugger/warnings.h"
#include "data_manager.h"

int data_counter = 0;

int variable_allocate() {
    CHECK_DATA(data_counter);
    return data_counter++;
}

void table_allocate(int n) {}