#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

int load_const(unsigned int val) {
    int reg = 0;

    if (val == 0)
        return reg;
    reg++;
    if (val == 1)
        return reg;
        
    int n = (int)log2(val) - 1;
    
    for(int mask = (1 << n); mask > 0; mask >>= 1) {
        reg <<= 1;
        if (mask & val)
            reg++;
    }
    printf("%u %d %u\n", val, n, reg);
    return reg;
}

int main() {
    // TEST LOAD_CONST 
    for(int i = 0; i <= 100; i++) {
        assert(i == load_const(i));
    }

    printf("%d", 1<<-1);
    printf("%d", 2<<-1);
}