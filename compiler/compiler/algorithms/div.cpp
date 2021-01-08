#include <cln/cln.h>
#include <iostream>

using namespace std;
using namespace cln;

int main() {
    cl_I val1 = 10000;
    cl_I val2 = 99;
    cl_I val3 = floor1(val1, val2);

    cout << val1 << " " << val2 << " " << val3 << endl;
}