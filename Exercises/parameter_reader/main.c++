// main.cpp
#include "parameters.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Check if a filename was provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <parameter_file>" << std::endl;
        return 1;
    }

    // Create a Parameters object
    Parameters params;
    
    // Read parameters from file
    if (!readParameters(argv[1], params)) {
        return 1;
    }
    
    // Use or display the parameters
    std::cout << "Parameters loaded:" << std::endl;
    std::cout << "wind = " << params.wind << std::endl;
    std::cout << "mass = " << params.mass << std::endl;
    std::cout << "useE = " << (params.useE ? "True" : "False") << std::endl;
    
    // Now you can use these parameters in your program
    
    return 0;
}
