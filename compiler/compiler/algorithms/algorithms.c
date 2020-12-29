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

/* dzielenie: 1
 * rejestrow: 5
 * zlozonosc: --
 */
void division1(int m, int n) {
    printf("%d / %d = ", m, n);

    int q = 0;

    int x = n;
    int y = 1;
    do {
        x <<= 1;
        y <<= 1;
    } while(x <= m);

    x >>= 1;
    y >>= 1;

    while(x >= n) {
        if (x <= m) {
            q += y;
            m -= x;
        }
        x >>= 1;
        y >>= 1;
    }

    printf("(%d,%d)\n", q, m);
}

/* dzielenie: 2
 * rejestrow: --
 * zlozonosc: --
 */
void division2(int n, int d) {
    int r = n;
    int k = 1;
    int q = 0;

    do {
        d <<= 1;
        k <<= 1;
    } while (k <= n);
    // d >>= 1;
    // k >>= 1;

    while (k > 0) {

        // printf("k = %d\n", k);
        // printf("r = %d\n", r);
        // printf("d = %d\n", r);
        // printf("\n");

        r <<= 1;
        if (r-d >= 0) {
            q += k;
            r -= d;
        }
        k >>= 1;   
    }

    printf("(%d)\n", q);
}


/* dzielenie:  --
 * rejestrow: --
 * zlozonosc: --
 */
int main() {
    // TEST DIV
    division2(23, 6);
    division2(24, 6);
    division2(25, 6);
}