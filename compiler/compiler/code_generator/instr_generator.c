#include "instr_generator.h"

/* pobiera wolny rejestr oraz umieszcza w nim podana stala */
int load_const(val_type val) {
    int reg = register_get();
    reset(reg);             // reg = 0

    // wartosc zerowa
    if (val == 0)
        return reg;
    
    // wartosc rozna od zera
    val_type n = (val_type)log2(val);
    for(val_type mask = (1 << n); mask > 0; mask >>= 1) {
        shl(reg);           // reg <<= 1
        if (mask & val)
            inc(reg);      // reg++;
    }
    return reg;
}
