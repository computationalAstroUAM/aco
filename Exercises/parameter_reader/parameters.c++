// parameters.cpp
#include "parameters.h"
#include <fstream>
#include <iostream>
#include <string>

bool readParameters(const std::string& filename, Parameters& params) {
    // Open the parameter file
    std::ifstream paramFile(filename);
    if (!paramFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    // Read and process the file line by line
    std::string line;
    while (std::getline(paramFile, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        // Find the position of the '=' character
        size_t equalPos = line.find('=');
        if (equalPos == std::string::npos) continue; // Skip lines without '='
        
        // Extract parameter name and value
        std::string paramName = line.substr(0, equalPos);
        std::string paramValue = line.substr(equalPos + 1);
        
        // Process each parameter
        if (paramName == "wind") {
            params.wind = std::stoi(paramValue);
        } else if (paramName == "mass") {
            params.mass = std::stod(paramValue);
        } else if (paramName == "useE") {
            params.useE = (paramValue == "True" || paramValue == "true" || paramValue == "1");
        }
    }

    paramFile.close();
    return true;
}
