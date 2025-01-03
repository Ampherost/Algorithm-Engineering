#include <iostream>
#include <chrono>
#include <cmath>

#define NEWTON_RAPHSON
// #define BINARY_SEARCH
// #define POLYNOMIAL


extern "C" void fastsqrt(const float* in, float* out, unsigned count) {
// Newton-Raphson iteration
#ifdef NEWTON_RAPHSON

// Binary Search Method
#elif defined(BINARY_SEARCH)

// Polynomial Method
#elif defined(POLYNOMIAL)

#endif
}