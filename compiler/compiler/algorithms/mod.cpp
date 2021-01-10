#include <cln/cln.h>
#include <iostream>

using namespace std;
using namespace cln;

void reg_mod_right_cln(cl_I a, cl_I b) {
    uintC n = integer_length(b);
    n = (n == 0) ? 0 : n-1;
    cl_I c = (cl_I(1) << n);

    if (c == b) {
        // cout << "OK" << endl;
        cl_I x = 1;
        cl_I y = 0;
        for( int i = 0; i < n; i++) {
            if ((a & 1) == 1) {
                y += x;
            }
            x <<= 1;
            a >>= 1;
        }
        cout << y << endl;
    }
    else {
        cout << "ERR" << endl;
    }
}
int main() {
    cl_I a = 5;
    cl_I b = 32;
    for (int i = 0; i <= 66; i++) {
        b = i;
        reg_mod_right_cln(a, b);
    }
    
}