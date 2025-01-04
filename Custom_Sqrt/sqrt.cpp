#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

#define NEWTON_RAPHSON
// #define BINARY_SEARCH
// #define POLYNOMIAL


extern "C" void fastsqrt(const float* in, float* out, unsigned count) {
// Newton-Raphson iteration
#ifdef NEWTON_RAPHSON
for (unsigned i = 0; i < count; ++i) {
        float x = in[i];
        float y = x / 2.0f;  // Initial guess
        const float tolerance = 1e-6;  // Precision tolerance
        
        // Iteratively improve the guess
        while (true) {
            float nextY = 0.5f * (y + x / y);
            if (fabs(nextY - y) < tolerance) {
                break;
            }
            y = nextY;
        }
        
        out[i] = y;  // Store the result
    }

// Binary Search Method
#elif defined(BINARY_SEARCH)

// Polynomial Method
#elif defined(POLYNOMIAL)

#endif
}

int main() {
    ifstream file("numbers.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return 1;
    }

    // Read numbers into a vector
    std::vector<float> numbers; // Dynamic array to store the numbers
    float num; // Temporary variable for reading from file
    while (file >> num) {
        numbers.push_back(num);
    }
    file.close();

    // Check if the file was empty
    if (numbers.empty()) {
        std::cerr << "Error: No numbers found in the file!" << std::endl;
        return 1;
    }

    // Prepare input and output arrays
    unsigned count = numbers.size();
    const float* in = numbers.data(); // Get raw pointer to vector data
    float* out = new float[count];    // Allocate output array

    // Call fastsqrt
    fastsqrt(in, out, count);

    // Print results and compare with std::sqrt
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Input\tfastsqrt\tstd::sqrt\tError" << std::endl;
    for (unsigned i = 0; i < count; ++i) {
        float std_sqrt = std::sqrt(in[i]);
        float error = fabs(out[i] - std_sqrt);
        std::cout << in[i] << "\t" << out[i] << "\t\t" << std_sqrt << "\t\t" << error << std::endl;
    }

    // Clean up
    delete[] out;
   
    return 0;
}