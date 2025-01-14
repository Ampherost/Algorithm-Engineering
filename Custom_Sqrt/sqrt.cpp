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

        // Bit manipulation
        union {
            float f;
            uint32_t i;
        } u;
        u.f = x;
        
        u.i = (u.i >> 1) + (63 << 23);
        
        float y = u.f; 
        
        y = 0.5f * (y + x / y);
        y = 0.5f * (y + x / y);
        y = 0.5f * (y + x / y);
        y = 0.5f * (y + x / y);
        
        out[i] = y;  // Store the result
    }

// Binary Search Method
#elif defined(BINARY_SEARCH)

// Polynomial Method
#elif defined(POLYNOMIAL)

#endif
}

/*
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
    std::cout << std::left
              << std::setw(10) << "Input"
              << std::setw(15) << "fastsqrt"
              << std::setw(15) << "std::sqrt"
              << std::setw(15) << "Error" 
              << std::endl;
              
    for (unsigned i = 0; i < count; ++i) {
        float std_sqrt = std::sqrt(in[i]);
        float error = fabs(out[i] - std_sqrt);
        std::cout << std::left
                  << std::setw(10) << in[i]
                  << std::setw(15) << out[i]
                  << std::setw(15) << std_sqrt
                  << std::setw(15) << error 
                  << std::endl;
    }

    // Clean up
    delete[] out;
   
    return 0;
}
*/