#include "instr_reg.h"

extern register_type registers[6];

void reg_const(int x, input_type val) {
    reset(x);
    if (val != 0) {
        input_type n = (input_type)log2(val) - 1;
        inc(x);
    
        for(input_type mask = (1 << n); mask > 0; mask >>= 1) {
            shl(x);
            if (mask & val) inc(x);
        }
    }
    DBG_RVAL(x);
}