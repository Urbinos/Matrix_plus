#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIXOOP_H_
#define CPP1_S21_MATRIXPLUS_S21_MATRIXOOP_H_

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  void FillMatrix(double* arr) const noexcept;
  bool CheckEqSizeMatrix(const S21Matrix& other) noexcept;

  S21Matrix& operator=(const S21Matrix& other) noexcept;
  S21Matrix& operator+(const S21Matrix& other);
  S21Matrix& operator-(const S21Matrix& other);
  S21Matrix& operator*(const double num);
  friend S21Matrix operator*(const double other, S21Matrix& tmp);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int rows, int cols);
  double operator()(int rows, int cols) const;

  int GetRows() const noexcept;
  void SetRows(int valueRows);
  int GetCols() const noexcept;
  void SetCols(int valueCols);

 private:
  int rows_{}, cols_{};  // Rows and columns
  double** matrix_ = nullptr;

  double DetCalc(double& result) noexcept;
  void SumOrSub(const S21Matrix& other, bool sum);
  void CreateMatrix() noexcept;
  void Minor(int rows, int cols, const S21Matrix& other) noexcept;
};

#endif  // CPP1_S21_MATRIXPLUS_S21_MATRIXOOP_H_
