// file: medium.cpp
#include <iostream>

int sumUpTo(int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += i;
    }
    return sum;
}

int main() {
    int target = 10;
    std::cout << "Sum from 1 to " << target << " is: " << sumUpTo(target) << std::endl;
    return 0;
}