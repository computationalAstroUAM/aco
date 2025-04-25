#include <iostream>
#include <vector>
#include <numeric> // for std::accumulate

float computeAverage(const std::vector<int>& nums) {
    int total = std::accumulate(nums.begin(), nums.end(), 0);
    return total / nums.size(); // Uh oh – integer division!
}

int main() {
    std::vector<int> data = {4, 5, 6};
    float avg = computeAverage(data);

    std::cout << "Data points: ";
    for (int n : data) std::cout << n << " ";
    std::cout << "\n";

    std::cout << "Calculated average: " << avg << std::endl;

    // Compare with actual average
    // float correct = static_cast<float>(std::accumulate(data.begin(), data.end(), 0)) / data.size();
    // std::cout << "Expected average:   " << correct << std::endl;

    return 0;
}