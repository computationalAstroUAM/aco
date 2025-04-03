#include <iostream>
#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <future>

// 1. Function Template
template<typename T>
T add(T a, T b) {
    return a + b;
}

// 2. Lambda Function
auto multiply = [](int a, int b) { return a * b; };

// 3. Function Object (Functor)
struct Adder {
    int operator()(int a, int b) const {
        return a + b;
    }
};

// 4. Function Pointer and Callback
void process(int data, void (*callback)(int)) {
    callback(data);
}

void printNumber(int num) {
    std::cout << "Number: " << num << std::endl;
}

// 5. Function Overloading
void configure(int width, int height = 100, bool fullscreen = false) {
    std::cout << "Configuring with width: " << width << std::endl;
}

void configure(const std::string& name) {
    std::cout << "Configuring with name: " << name << std::endl;
}

// 6. Default Arguments
void setup(int width, int height = 100, bool fullscreen = false) {
    std::cout << "Setting up with width: " << width 
              << ", height: " << height 
              << ", fullscreen: " << fullscreen << std::endl;
}


int main() {
    // 1. Function Template 
    // Allows functions to work with multiple data types and Enables generic programming
    std::cout << "Function Template: " << add(5, 3) << std::endl;
    std::cout << "Function Template: " << add<int>(5, 3) << std::endl;
    std::cout << "Function Template: " << add(5.5, 3.3) << std::endl;
    std::cout << "Function Template: " << add<double>(5.5, 3.3) << std::endl;
    // can you do add string? like this: see more in the function overloading part
    // std::cout << "Function Template: " << add<std::string>("Hello", "World") << std::endl;

    // 2. Lambda Function
    // Allows you to define anonymous functions inline
    // Can capture variables from their environment
    std::cout << "Lambda Function: " << multiply(4, 5) << std::endl;

    auto printIfEven = [](int num) {
        if (num % 2 == 0) {
            std::cout << "Even number: " << num << std::endl;
        }
    };
    printIfEven(4);
    // [=] - captures all variables by value
    // [&] - captures all variables by reference
    // [var] - captures specific variable by value
    // [&var] - captures specific variable by reference

    // 3. Function Object
    Adder adder;
    std::cout << "Function Object: " << adder(6, 7) << std::endl;
    //what if you replace the operator() with other function?

    // 4. Function Pointer and Callback
    // Pass functions as arguments
    process(10, printNumber);

    // 5. Function Overloading
    configure(800);
    configure("Custom Configuration");

    // 6. Default Arguments
    setup(800);
    setup(800, 600);
    setup(800, 600, true);

    return 0;
}
