#include "data_manager.hpp"
#include "../debugger/warnings.hpp"
#include "../debugger/debugger.hpp"

data_type data_counter = 0;

data_type variable_allocate() {
    CHECK_DATA(data_counter);
    DBG_ALLOCATE_VARIABLE(data_counter);
    return data_counter++;
}

data_type array_allocate(data_type n) {
    data_type temp = data_counter;
    data_counter += n;
    CHECK_DATA(data_counter);
    DBG_ALLOCATE_ARRAY(temp, data_counter);
    return temp;
}