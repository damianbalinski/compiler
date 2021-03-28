#include <cln/integer.h>
#include <cln/cln.h>
#include <iostream>

using namespace std;
using namespace cln;

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

void reg_mul_two_power_cln(cl_I val1, cl_I val2) {
    uintC n = integer_length(val1);
    n = (n == 0) ? 0 : n-1;
    cl_I val3 = (cl_I(1) << n);
    cout << val1 << " " << val3 << " " << (val1 == val3) << endl;
}

void reg_mul_cln(cl_I x, cl_I y) {
    cl_I z(0);
    cout << x * y << " ";

    while (y != 0) {
        if ((y & 1) == 1)
            z += x;
        x <<= 1;
        y >>= 1;
    }
    
    cout << z << endl;
}

int main() {

    // TEST REG_MUL_TWO_POWER_CLN
    // cl_I val1 = 1024;
    // cl_I val2 = 100000;
    // for(int i = 0; i <= 10; i++) {
    //     val1 = i;
    //     reg_mul_two_power_cln(val1, val2);
    // }

    

    // TEST REG_MUL_CLN
    cl_I val1 = "23";
    cl_I val2 = "23";

    reg_mul_cln(val1, val2);
    // cl_I val1 = 10000;
    // cl_I val2 = 10000;
    // for (int i = 0; i < 100; i++) {
    //     val2 = i;
    //     reg_mul_cln(val1, val2);
    // }
}