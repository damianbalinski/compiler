#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

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

int mult(int x, int y) {
    int z = 0;
    while (true) {
        if (y & 1)
            z += x;
        if (y == 0)
            break;
        x <<= 1;
        y >>= 1;
    }

    return z;
}

int main() {
    // TEST MULT
    for(int i = 0; i < 100000000; i++) {
        int x = rand();
        int y = rand();
        assert(mult(x,y) == x*y);
    }
}