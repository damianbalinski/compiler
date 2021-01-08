#include <cstdlib>
#include "unit.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"

unit_type* unit_alloc() {
    unit_type* unit = new unit_type;
    unit->val = -1;
    DBG_UNIT_ALLOC(unit);
    CHECK_UNIT(unit);
    return unit;
}

void unit_free(unit_type* unit) {
    DBG_UNIT_FREE(unit);
    delete unit;
}