#include "s21_matrix_oop.h"

#include <cmath>
#include <iostream>

S21Matrix::S21Matrix() : matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::out_of_range("invalid arguments for create matrix");
  }
  CreateMatrix();
}

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Конструктор перемещения
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

// Деструктор
S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      if (matrix_) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) noexcept {
  bool result = CheckEqSizeMatrix(other);
  for (int i = 0; i < rows_ && result; ++i) {
    for (int j = 0; j < cols_ && result; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
        result = false;
      }
    }
  }
  return result;
}
void S21Matrix::SumMatrix(const S21Matrix& other) { SumOrSub(other, true); }

void S21Matrix::SubMatrix(const S21Matrix& other) { SumOrSub(other, false); }

void S21Matrix::SumOrSub(const S21Matrix& other, bool sum) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (sum) {
        matrix_[i][j] += other.matrix_[i][j];
      } else {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::exception();
  }
  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = temp;
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix temp(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      temp.matrix_[i][j] = matrix_[j][i];
    }
  }
  return *this = temp;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::exception();
  }
  if (cols_ == 1) {
    matrix_[0][0] = 1;
  } else {
    S21Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix minor(rows_, cols_);
        minor.SetRows(rows_ - 1);
        minor.SetCols(cols_ - 1);
        Minor(i, j, minor);
        double temp = 0;
        minor.DetCalc(temp);
        result.matrix_[i][j] = temp * pow(-1, i + j);
      }
    }
    *this = result;
  }
  return *this;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::exception();
  }
  double result = 0.0;
  return DetCalc(result);
}

double S21Matrix::DetCalc(double& result) noexcept {
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix temp(rows_, cols_);
    result = 0.0;
    int degree = 1;
    for (int i = 0; i < cols_; ++i) {
      temp.SetRows(rows_ - 1);
      temp.SetCols(cols_ - 1);
      Minor(0, i, temp);
      double tempResult = 0.0;
      temp.DetCalc(tempResult);
      result += (degree * matrix_[0][i] * tempResult);
      degree = -degree;
    }
  }
  return result;
}

void S21Matrix::Minor(int rows, int cols, const S21Matrix& other) noexcept {
  int flag_rows = 0;
  for (int i = 0; i < rows_ - 1; ++i) {
    if (i == rows) {
      flag_rows = 1;
    }
    int flag_columns = 0;
    for (int j = 0; j < rows_ - 1; ++j) {
      if (j == cols) {
        flag_columns = 1;
      }
      other.matrix_[i][j] = matrix_[i + flag_rows][j + flag_columns];
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = DetCalc(determinant);
  if (determinant == 0) {
    throw std::exception();
  }
  S21Matrix temp(*this);
  temp.CalcComplements();
  temp.Transpose();
  temp.MulNumber(1.0 / determinant);
  *this = temp;
  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) noexcept {
  if (this == &other) return *this;
  S21Matrix temp(other);
  std::swap(rows_, temp.rows_);
  std::swap(cols_, temp.cols_);
  std::swap(matrix_, temp.matrix_);
  return *this;
}

S21Matrix& S21Matrix::operator+(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*(const double num) {
  MulNumber(num);
  return *this;
}

/* Умножение числа на матрицу */
S21Matrix operator*(const double other, S21Matrix& tmp) {
  tmp *= other;
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  S21Matrix::SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  S21Matrix::SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  S21Matrix::MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  S21Matrix::MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int rows, int cols) {
  if (rows >= rows_ || cols >= cols_) {
    throw std::exception();
  }
  if (rows < 0 || cols < 0) {
    throw std::exception();
  }
  return matrix_[rows][cols];
}

double S21Matrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_) {
    throw std::exception();
  }
  if (rows < 0 || cols < 0) {
    throw std::exception();
  }
  return matrix_[rows][cols];
}

int S21Matrix::GetRows() const noexcept { return rows_; }

void S21Matrix::SetRows(int valueRows) {
  if (valueRows < 1) {
    throw std::underflow_error("wrong number of lines");
  }
  S21Matrix temp(valueRows, cols_);
  for (int i = 0; i < valueRows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i >= rows_) {
        temp.matrix_[i][j] = 0.0;
      } else {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = temp;
}

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetCols(int valueCols) {
  if (valueCols < 1) {
    throw std::underflow_error("wrong number of columns");
  }
  S21Matrix temp(rows_, valueCols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < valueCols; ++j) {
      if (j >= cols_) {
        temp.matrix_[i][j] = 0.0;
      } else {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = temp;
}

void S21Matrix::CreateMatrix() noexcept {
  if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]{};
    }
  }
}

void S21Matrix::FillMatrix(double* arr) const noexcept {
  int count = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = arr[count];
      count++;
    }
  }
}

bool S21Matrix::CheckEqSizeMatrix(const S21Matrix& other) noexcept {
  int result = false;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    result = true;
  }
  return result;
}
