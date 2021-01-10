#include "data_manager.hpp"
#include "../debugger/warnings.hpp"
#include "../debugger/debugger.hpp"

input_type data_counter = 0;

input_type variable_allocate() {
    CHECK_DATA(data_counter);
    DBG_ALLOCATE_VARIABLE(data_counter);
    return data_counter++;
}

input_type array_allocate(input_type n) {
    input_type temp = data_counter;
    data_counter += n;
    CHECK_DATA(data_counter);
    DBG_ALLOCATE_ARRAY(temp, data_counter);
    return temp;
}