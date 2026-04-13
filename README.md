# Algorithm-Engineering
 
A collection of efficient algorithms and solutions designed with practicality and performance to tackle common tough software problems. This repository emphasizes innovative approaches to problem-solving, optimization techniques, and clean, maintainable code. Ideal for deepening one's understanding of algorithm design and engineering.
 
## Projects
 
### Compression
 
A Huffman encoding implementation in C++ for lossless text compression. The algorithm builds an optimal prefix-code tree from character frequencies, serializes the tree alongside the encoded data into a compact bitstream, and supports full round-trip compression and decompression. Achieves an approximate compression ratio of 1.7x on typical text inputs.
 
### Custom Sqrt
 
A fast square root approximation leveraging the structure of IEEE 754 floating-point numbers. The initial guess is produced by halving the exponent bits directly through integer manipulation, providing a surprisingly close starting point. This estimate is then refined through Newton-Raphson iterations, striking a balance between speed and accuracy. The result closely matches `std::sqrt` with minimal error.
 
### Matrix Multiply
 
A matrix multiplication module supporting both dense and sparse representations. The sparse format encodes rows as alternating runs of zero and non-zero counts, storing only non-zero values to reduce memory usage and computation on large, sparse matrices.
 
### Quicksort Pivot
 
A pivot selection strategy for quicksort implemented in Python. Uses median-of-three (low, middle, high elements) to choose the pivot, reducing the likelihood of worst-case partitioning on sorted or nearly sorted inputs. The framework includes an opcode counter to measure computational cost of the pivot selection logic.
 