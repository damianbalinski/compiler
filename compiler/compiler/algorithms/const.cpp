#include <iostream>
#include <math.h>
#include <cln/cln.h>
#include <cln/condition.h>

using namespace std;
using namespace cln;

int reg_const(unsigned int val) {
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


/* Umieszcza stala w rejestrze. */
cl_I reg_const_num(cl_I& val) {

    static const cl_I ZERO(0);
    static const cl_I ONE(1);

    cl_I x(0);

    if (equal(val, ZERO)) {
        return x;
    }
        
    x++;
    if (equal(val, ONE)) {
        return x;
    }
        
    uintC n = integer_length(val)-2;
    for(cl_I mask = (ONE<<n); mask > ZERO; mask >>= ONE) {
        x <<= ONE;
        if ((mask & val) != ZERO) x++;
    }
    return x;
}

int main() {

    cl_I val;
    cl_I num;

    // TEST1
    val = "1000000000011111000000000000000000000099999000000000000000000000000111110000000000000";
    num = reg_const_num(val);
    cout << val << endl;
    cout << num << endl;

    // TEST 2
    // for (int i = -2; i < 1000; i++) {
    //     val = i;
    //     num = reg_const_num(val);
    //     cout << val << " " << num << endl;
    // }

}