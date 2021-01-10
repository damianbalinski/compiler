#include <cstdlib>
#include "unit.hpp"
#include "const.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"
#include "../code_generator/registers.hpp"
#include "../code_generator/code_generator.hpp"

unit_type* unit_alloc() {
    unit_type* unit = new unit_type;
    unit->reg = NOTHING;
    unit->val = CLN_NOTHING;
    unit->offset_cln = CLN_NOTHING;
    DBG_UNIT_ALLOC(unit);
    CHECK_UNIT(unit);
    return unit;
}

void unit_free(unit_type* unit) {
    DBG_UNIT_FREE(unit);
    delete unit;
}

unit_type* unit_copy(unit_type* unit) {
    unit_type* unit2 = new unit_type;
    CHECK_UNIT_COPY(unit->val, unit->reg);

    if(unit->val != CLN_NOTHING) {
        // COPY VAL
        DBG_UNIT_COPY("value");
        unit2->reg = NOTHING;
        unit2->val = unit->val;
        unit2->offset_cln = CLN_NOTHING;
    }
    else {
        // COPY TEMP REG
        DBG_UNIT_COPY("temp register");
        unit2->reg = SUPER_REGISTER;
        unit2->val = CLN_NOTHING;
        unit2->offset_cln = CLN_NOTHING;
        reset(SUPER_REGISTER);
        add(SUPER_REGISTER, unit->reg);
    }
    return unit2;
}