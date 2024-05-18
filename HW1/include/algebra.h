#ifndef AUT_AP_2024_Spring_HW1
#define AUT_AP_2024_Spring_HW1

#include <format>       // Required for text formatting
#include <iostream>     // Required for standard input-output operations
#include <optional>     // Required for handling optional arguments
#include <random>       // Required for generating random numbers
#include <type_traits>  // Required for type traits
#include <vector>       // Required for vector data structure

namespace algebra {
// Matrix data structure
template <typename T>
using MATRIX = std::vector<std::vector<T>>;

// Matrix initialization types
enum class MatrixType { Zeros, Ones, Identity, Random };

// Function template for matrix initialization
template <typename T>
MATRIX<T> create_matrix(std::size_t rows, std::size_t columns,
                        std::optional<MatrixType> type = MatrixType::Zeros,
                        std::optional<T> lowerBound = std::nullopt,
                        std::optional<T> upperBound = std::nullopt) {
  // Check if the matrix type is set to Random.
  // If so, ensure that both upperBound and lowerBound values are provided.
  if (type.value() == MatrixType::Random) {
    // Check if upperBound has been provided. If not, raise an exception.
    if (!upperBound.has_value()) {
      throw std::invalid_argument("Upper bound must be provided");
    }

    // Check if lowerBound has been provided. If not, raise an exception.
    if (!lowerBound.has_value()) {
      throw std::invalid_argument("Lower bound must be provided");
    }
  }

  if (rows <= 0)
    throw std::invalid_argument("lowerBound should be greater than zero");

  if (columns <= 0)
    throw std::invalid_argument("upperBound should be greater than zero");

  // Check if lowerBound is less than upperBound
  if (lowerBound.value_or(0) >= upperBound.value_or(1)) {
    throw std::invalid_argument("lowerBound should be less than upperBound");
  }

  // Initialize matrix with specified type
  MATRIX<T> matrix(rows, std::vector<T>(columns));

  // Initialize matrix based on specified type
  switch (type.value()) {
    case MatrixType::Zeros:
      for (auto& row : matrix) {
        std::fill(row.begin(), row.end(), static_cast<T>(0));
      }
      break;
    case MatrixType::Ones:
      for (auto& row : matrix) {
        std::fill(row.begin(), row.end(), static_cast<T>(1));
      }
      break;
    case MatrixType::Identity:
      if (rows != columns) {
        throw std::invalid_argument("Identity matrix must be square.");
      }
      for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < columns; ++j) {
          matrix[i][j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
        }
      }
      break;
    case MatrixType::Random:
      // Random number generator setup
      std::mt19937 gen(std::random_device{}());

      using uniform_distribution = typename std::conditional<
          std::is_floating_point<T>::value, std::uniform_real_distribution<T>,
          typename std::conditional<std::is_integral<T>::value,
                                    std::uniform_int_distribution<T>,
                                    void>::type>::type;

      uniform_distribution dist(lowerBound.value_or(0), upperBound.value_or(1));
      for (auto& row : matrix)
        for (auto& element : row) element = dist(gen);

      break;
  }

  return matrix;
}

// Function template to display matrix elements
template <typename T>
void display(const MATRIX<T>& matrix) {
  for (auto& row : matrix) {
    for (auto& element : row) {
      std::cout << std::format("|{:>7}", element);
    }
    std::cout << std::format("|\n");
  }
}

// Function template to perform matrix addition or subtraction
template <typename T>
MATRIX<T> sum_sub(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB,
                  std::optional<std::string> operation = "sum") {
  if ((matrixA.size() == 0) & (matrixB.size() == 0)) return MATRIX<T>{};

  // Check if matrixA and matrixB have the same size
  if ((matrixA.size() != matrixB.size()) ||
      (matrixA[0].size() != matrixB[0].size()))
    throw std::invalid_argument("matrix A and B should have the same size");

  // Perform matrix addition or subtraction based on the operation
  if (operation == "sub") {
    MATRIX<T> matrixC = matrixA;
    for (std::size_t i = 0; i < matrixA.size(); i++)
      for (std::size_t j = 0; j < matrixA[0].size(); j++)
        matrixC[i][j] -= matrixB[i][j];
    return matrixC;

  } else {
    MATRIX<T> matrixC = matrixA;
    for (std::size_t i = 0; i < matrixA.size(); i++)
      for (std::size_t j = 0; j < matrixA[0].size(); j++)
        matrixC[i][j] += matrixB[i][j];
    return matrixC;
  }
}

// scalar multiplication
template <typename T>
MATRIX<T> multiply(const MATRIX<T>& matrix, const T scalar) {
  // Create a new matrix 'matrixC' and initialize it with the elements of the
  // input matrix.
  MATRIX<T> matrixC = matrix;
  // Iterate over each row of the matrix.
  for (std::size_t i = 0; i < matrix.size(); i++)
    for (std::size_t j = 0; j < matrix[0].size(); j++)
      matrixC[i][j] = matrix[i][j] * scalar;

  return matrixC;
}

// Matrix multiplication function
template <typename T>
MATRIX<T> multiply(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB) {
  // Check for empty matrices
  if ((matrixA.size() == 0) | (matrixB.size() == 0))
    throw std::invalid_argument("empty matrices with matrix multiplication");

  // Check for dimension mismatch
  if (matrixA[0].size() != matrixB.size())
    throw std::invalid_argument("dimension mismatch");

  // Create result matrix initialized with zeros
  MATRIX<T> matrixC =
      create_matrix<int>(matrixA.size(), matrixB[0].size(), MatrixType::Zeros);

  // Perform matrix multiplication
  for (std::size_t i = 0; i < matrixA.size(); i++) {
    for (std::size_t k = 0; k < matrixB[0].size(); k++) {
      int sum{0};
      for (std::size_t j = 0; j < matrixA[0].size(); j++)
        sum += matrixA[i][j] * matrixB[j][k];
      matrixC[i][k] = sum;
    }
  }
  return matrixC;
}

// Hadamard Product: Element-wise multiplication of matrices
template <typename T>
MATRIX<T> hadamard_product(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB) {
  // Return an empty matrix if either matrixA or matrixB is empty
  if ((matrixA.size() == 0) & (matrixB.size() == 0)) return MATRIX<T>{};

  // Check if matrixA and matrixB have the same size
  if ((matrixA.size() != matrixB.size()) ||
      (matrixA[0].size() != matrixB[0].size()))
    throw std::invalid_argument("matrix A and B should have the same size");

  // Perform element-wise multiplication of matrixA and matrixB
  MATRIX<T> matrixC = matrixA;
  for (std::size_t i = 0; i < matrixA.size(); i++) {
    for (std::size_t j = 0; j < matrixA[0].size(); j++)
      matrixC[i][j] = matrixA[i][j] * matrixB[i][j];
  }

  return matrixC;
}

// Transposing a square matrix
template <typename T>
MATRIX<T> transpose(const MATRIX<T>& matrix) {
  // Return an empty matrix if the input matrix is empty
  if (matrix.size() == 0) return MATRIX<T>{};

  // Create a new matrix 'matrixC' to store the transposed matrix
  MATRIX<T> matrixC =
      create_matrix<T>(matrix[0].size(), matrix.size(), MatrixType::Zeros);

  // Perform transposition by iterating over each element of the input matrix
  // and assigning its transpose to the corresponding position in the new matrix
  // 'matrixC'
  for (std::size_t i = 0; i < matrix.size(); i++)
    for (std::size_t j = 0; j < matrix[0].size(); j++)
      matrixC[j][i] = matrix[i][j];

  // Return the transposed matrix 'matrixC'
  return matrixC;
}

// calculating the trace of a square matrix
template <typename T>
T trace(const MATRIX<T>& matrix) {
  if (matrix.size() == 0)
    throw std::invalid_argument("The input matrix should not be empty");

  if (matrix.size() != matrix[0].size())
    throw std::invalid_argument("matrix should be square");

  int trc{0};
  for (std::size_t i = 0; i < matrix.size(); i++)
    for (std::size_t j = 0; j < matrix[0].size(); j++)
      if (i == j) trc += matrix[i][j];

  return trc;
}

// Define the permutations function
std::vector<std::vector<int>> permutations(std::vector<int> x);

// Define the sgn function
int sgn(std::vector<int> ls);

// Define the determinant function
template <typename T>
double determinant(const MATRIX<T>& matrix) {
  if (matrix.size() == 0)
    throw std::invalid_argument("The input matrix should not be empty");

  if (matrix.size() != matrix[0].size())
    throw std::invalid_argument("matrix should be square");

  std::vector<int> indices(matrix.size());
  std::iota(indices.begin(), indices.end(), 0);

  auto perm = permutations(indices);
  double res = 0;

  for (const auto& i : perm) {
    int p = sgn(i);
    int cnt = 0;
    for (const auto& j : i) {
      p *= matrix[cnt][j];
      cnt++;
    }
    res += p;
  }

  return res;
}

template <typename T>
MATRIX<double> inverse(const MATRIX<T>& matrix) {
  // if(std::static_cast<double>(0) == determinant(matrix)) throw
  double det = determinant(matrix);
  if (det == static_cast<double>(0))
    throw std::invalid_argument(
        "This matrix has no inverse (determinant is zero).");

  MATRIX<T> cofactorM =
      create_matrix<T>(matrix.size(), matrix[0].size(), MatrixType::Zeros);

  for (std::size_t i = 0; i < matrix.size(); i++)
    for (std::size_t j = 0; j < matrix[0].size(); j++) {
      MATRIX<T> temp = matrix;
      temp.erase(temp.begin() + i);
      for (size_t t = 0; t < matrix[0].size() - 1; t++)
        temp[t].erase(temp[t].begin() + j);
      if ((i + j) % 2 == 1)
        cofactorM[i][j] = -1 * determinant(temp);
      else
        cofactorM[i][j] = determinant(temp);
    }

  MATRIX<T> adjointM = transpose(cofactorM);

  MATRIX<T> invM = multiply(adjointM, 1 / determinant(matrix));

  return invM;
}

}  // namespace algebra

#endif  // AUT_AP_2024_Spring_HW1
