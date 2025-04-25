// parameters.h
#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

struct Parameters {
    int wind = 0;
    double mass = 0.0;
    bool useE = false;
};

bool readParameters(const std::string& filename, Parameters& params);

#endif // PARAMETERS_H
