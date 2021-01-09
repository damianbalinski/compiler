#include <cln/cln.h>
#include <iostream>

using namespace std;
using namespace cln;

int main() {
    cl_I val1 = 1024;
    cl_I val2 = 0;

    cl_I val3 = mod(val1, val2);
    cout << val3 << endl;
}