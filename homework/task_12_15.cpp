#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string filename = "numbers.txt";
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return 1;
    }

    double value = 0.0;
    double log_sum = 0.0;
    size_t count = 0;

    while (in >> value) {
        if (value <= 0.0) {
            std::cerr << "Geometric mean requires positive numbers, got: " << value << "\n";
            return 1;
        }
        log_sum += std::log(value);
        ++count;
    }

    if (count == 0) {
        std::cerr << "File is empty or has no valid numbers.\n";
        return 1;
    }

    double geom_mean = std::exp(log_sum / static_cast<double>(count));
    std::cout << "Count: " << count << "\n";
    std::cout << "Geometric mean: " << std::fixed << std::setprecision(6) << geom_mean << "\n";
    return 0;
}