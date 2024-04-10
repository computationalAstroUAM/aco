//
// Created by weiguang on 10/04/24.
/*In both C and C++, you can pass parameters to functions either by value or by reference.
 *
 * When you pass a parameter by value, a copy of the argument is made for the function to use, and changes made to the
 * parameter inside the function do not affect the original argument.  When you pass a parameter by reference, the function
 * works directly with the original argument, and changes made to the parameter inside the function do affect the original
 * argument.
 *
 * In C, you can simulate pass-by-reference behavior using pointers, but in C++, you can pass parameters by reference
 * directly using the & symbol.*/
//
#include <iostream>

void updateByValue(int x) {
    x = 10;
}

void updateByReference(int& x) {
    x = 20;
}

int main() {
    int a = 5;
    updateByValue(a);
    std::cout << a << std::endl; // Outputs: 5

    updateByReference(a);
    std::cout << a << std::endl; // Outputs: 20

    return 0;
}