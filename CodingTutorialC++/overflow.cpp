#include <iostream> // for cout and endl
#include <climits>  // for INT_MAX and INT_MIN
#include <cfloat>   // for FLT_MAX
#include <cmath>    // for round
#include <iomanip> // for setprecision

using namespace std;

int main(int argc, char **argv) {
#ifdef nooutput
    cout << "Hello, World!" << endl;
#endif
    //Integer Overflow/Underflow problem
    int max_int = INT_MAX;
    cout << "Max int: " << max_int << endl;

    // Attempt to add 1 to max_int, causing an overflow
    max_int = max_int + 1;
    cout << "Max int + 1: " << max_int << endl;

    int min_int = INT_MIN;
    cout << "Min int: " << min_int << endl;

    // Attempt to remove 1 to min_int, causing an underflow
    min_int = min_int - 1;
    cout << "Min int - 1: " << min_int << endl;

//    float overflow problem
    float max_float = FLT_MAX;
    std::cout << "Max float: " << max_float << std::endl;

    // Attempt to multiply max_float by itself, causing an overflow
    float overflow_float = max_float * max_float;
    std::cout << "Max float * Max float: " << overflow_float << std::endl;

    //--------------------------------------------------------------------------------------------
    //   "floating point precision error".
    //  In computer programming, floating point numbers are represented with a certain level of precision.
    //  This means that after a certain number of decimal places, the exact value of a floating point number
    //  cannot be accurately represented.
    //
    //  In this case, the value 16777216.0 is a large floating point number. When you try to add a small number like 1.0 or 10.0 to it,
    //  the added value may not affect the least significant digits of the large number due to the limits of floating point precision.
    //  This can lead to unexpected results, as the output might not reflect the arithmetic you'd expect.
    //
    //  The last operation, g = f+16777216.0, is large enough to affect the significant digits of f, so it results in a change.
    //  This is a common issue when dealing with floating point numbers in many programming languages, not just C++.
    //--------------------------------------------------------------------------------------------
    float f, g;
    f = 16777216.0;
    g = f + 1.0;
    cout << setprecision(10) << f << "+1.0       =" << g << endl;
    g = f + 10.0;
    cout << setprecision(10) << f << "+10.0      =" << g << endl;
    g = f + 16777216.0;
    cout << setprecision(10) << f << "+16777216 =" << g << endl;

    return 0;
}
