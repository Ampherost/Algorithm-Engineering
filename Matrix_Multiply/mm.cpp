#include <vector>
#include <iostream>

// A NxN sparse representation
typedef std::vector<unsigned> zero_nonzero;
struct Sparse {
  // Invariant: len(rows) == N
  // Invariant: sum(x for x in row[i]) == N
  // Invariant: len(values) == sum(all non-zero counts)
  // Invariant: rows[i][j] is a count of zeros where j is even
  // We represent rows like this:
  // 0 0 4 5 0    (2,2,1)    2+2+1 = 5
  // 1 2 3 0 4    (0,3,1,1)  0+3+1+1 = 5
  // 0 0 0 0 0    (5)        5 = 5
  // 1 1 1 1 1    (0,5)      0+5 = 5
  // values holds only the non-zero entries
  // 4 5 1 2 3 4 1 1 1 1 1
  
  std::vector<zero_nonzero> rows;  // form: zeros,non,zeros,non...
  std::vector<double> values;
  unsigned N() const { return rows.size(); }
};

// X and Y are both aligned on 4096 byte boundaries
void sparse_mm(int N, const Sparse& A, const double* X, double* Y) {

}

// A, X, and Y are all aligned on 4096 byte boundaries
void mm(int N, const double* A, const double* X, double* Y) {

}