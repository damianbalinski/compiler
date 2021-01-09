#include <cln/cln.h>
#include <iostream>
#include <assert.h>

#define QUOTIENT true
#define REMAINDER false

using namespace std;
using namespace cln;

int division0(int m, int n, bool type) {
    if (type == QUOTIENT)
        return n == 0 ? 0 : m/n;
    else
        return n == 0 ? 0 : m%n;
}

int division1(int r, int n, bool type) {
    int q = 0;
    int x;
    int y;
    int f;
    if (n != 0) {
        
        x = n;
        y = 1;
        while(f = x - r, f <= 0) {
            x <<= 1;
            y <<= 1;
        }
        while(f = n-x, f <= 0) {
            if (f = x - r, f <= 0) {
                q += y;
                r -= x;
            }
            x >>= 1;
            y >>= 1;
        }
    }
    else {
        r = 0;
    }

    if (type == QUOTIENT)
        return q;
    else
        return r;
}

// int division2(int r, int n, bool type) {
//     int q = 0;
//     int y;
//     int x;
//     int f;

//     if (n != 0) {
//         while( f = r-n, f >= 0 ) {
//             x = n;
//             y = 1;
            
//             while( f = x<<1, f < r )
//             {
//                 x <<= 1;
//                 y <<= 1;
//             }

//             q += y;
//             r -= x;
//         }
//     }
//     else {
//         r = 0;
//     }

//     if (type == QUOTIENT)
//         return q;
//     else
//         return r;
// }

int main() {
    // TEST DIV
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 120; j++) {
            assert(division0(i, j, QUOTIENT) == division1(i, j, QUOTIENT));
            assert(division0(i, j, REMAINDER) == division1(i, j, REMAINDER));
            // assert(division0(i, j, QUOTIENT) == division2(i, j, QUOTIENT));
            // assert(division0(i, j, REMAINDER) == division2(i, j, REMAINDER));

            printf("%d / %d  =  [%d, %d] OK\n", i, j, j == 0 ? 0 : i/j, j == 0 ? 0 : i%j);
        }
        printf("\n");
    }
    printf("END\n");
}