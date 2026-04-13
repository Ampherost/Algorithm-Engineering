#include <vector>
#include <iostream>

// A NxN sparse representation
typedef std::vector<unsigned> zero_nonzero;
struct Sparse {
  // Invariant: rows.size() == number of rows.
  // Invariant: For each row, the sum of the counts equals the number of columns.
  // Invariant: The counts at even indices represent numbers of consecutive zeros,
  //            while counts at odd indices represent numbers of consecutive nonzero values.
  // For example, the row:
  //   0 0 4 5 0    -> counts: {2, 2, 1}
  // has 2 zeros, then 2 nonzeros (4 and 5), then 1 zero.
  std::vector<zero_nonzero> rows;  // each row stored as alternating counts: zeros, nonzeros, ...
  std::vector<double> values;      // nonzero entries in row–major order
  unsigned N() const { return rows.size(); }
};

// Optimized sparse matrix-vector multiplication.
void sparse_mm(int N, const Sparse& A, const double* X, double* Y) {
    size_t val_index = 0; // global index into A.values
    for (int i = 0; i < N; i++) {
        double sum = 0;
        unsigned col = 0;
        const auto& row_counts = A.rows[i];
        size_t segs = row_counts.size();
        size_t k = 0;
        // Process pairs of segments: first a skip (zeros) then a nonzero block.
        while (k + 1 < segs) {
            // Skip zeros.
            col += row_counts[k];
            // Process nonzeros.
            unsigned count = row_counts[k+1];
            const double* x_ptr = X + col;
            unsigned j = 0;
            // Unroll inner loop by a factor of 4.
            while (j + 3 < count) {
                sum += A.values[val_index]   * x_ptr[j] +
                       A.values[val_index+1] * x_ptr[j+1] +
                       A.values[val_index+2] * x_ptr[j+2] +
                       A.values[val_index+3] * x_ptr[j+3];
                j += 4;
                val_index += 4;
            }
            for (; j < count; j++) {
                sum += A.values[val_index++] * x_ptr[j];
            }
            col += count;
            k += 2;
        }
        // If there is a trailing zeros segment.
        if (k < segs) {
            col += row_counts[k];
        }
        Y[i] = sum;
    }
}

// Optimized dense matrix-vector multiplication.
// A is a square matrix (N x N) stored in row–major order.
void mm(int N, const double* A, const double* X, double* Y) {
    for (int i = 0; i < N; i++) {
        double sum = 0;
        const double* a_row = A + i * N;
        int j = 0;
        int limit = N - (N % 4);  // unroll loop in chunks of 4
        for (; j < limit; j += 4) {
            sum += a_row[j]   * X[j] +
                   a_row[j+1] * X[j+1] +
                   a_row[j+2] * X[j+2] +
                   a_row[j+3] * X[j+3];
        }
        for (; j < N; j++) {
            sum += a_row[j] * X[j];
        }
        Y[i] = sum;
    }
}

