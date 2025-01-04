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
   
    return 0;
}