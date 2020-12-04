#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

int load_const(int val) {
    int reg = 0;

    if (val == 0)
        return reg;

    int n = (int)log2(val) - 1;
        reg++;
    for(int mask = (1 << n); mask > 0; mask >>= 1) {
        reg <<= 1;
        if (mask & val)
            reg++;
    }
    return reg;
}

int main() {
    // TEST LOAD_CONST 
    for(int i = 0; i <= 1000000; i++) {
        assert(i == load_const(i));
    }
}