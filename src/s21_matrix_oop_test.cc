#include "s21_matrix_oop.h"

#include "gtest/gtest.h"

using std::exception;
using std::underflow_error;

TEST(TestGroup, Print) { ASSERT_TRUE(1 == 1); }

TEST(Constructor, CONSTRUCTOR_1_1) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_EQ(A.GetCols(), B.GetCols());
  EXPECT_EQ(A.GetRows(), B.GetRows());
}

TEST(Constructor, CONSTRUCTOR_2_1) {
  S21Matrix A(2, 3);
  EXPECT_EQ(2, A.GetRows());
  EXPECT_EQ(3, A.GetCols());
}

TEST(Constructor, CONSTRUCTOR_2_3) {
  EXPECT_THROW(S21Matrix A(-20, 3), exception);
}

TEST(Constructor, CONSTRUCTOR_2_4) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 3);
  EXPECT_EQ(2, A.GetRows());
  EXPECT_EQ(3, A.GetCols());
}

TEST(Constructor, CONSTRUCTOR_3_1) {
  S21Matrix A(3, 3);
  double arr[] = {3, 5, 7, 9, 8, 6, 0, 1, 2};
  A.FillMatrix(arr);
  S21Matrix B(A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(A(i, j), B(i, j));
    }
  }
  EXPECT_EQ(A.GetCols(), B.GetCols());
  EXPECT_EQ(A.GetRows(), B.GetRows());
}

TEST(Constructor, CONSTRUCTOR_4_1) {
  S21Matrix A(3, 3);
  double arr[] = {3, 5, 7, 9, 8, 6, 0, 1, 2};
  A.FillMatrix(arr);
  S21Matrix B(std::move(A));
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(arr[count], B(i, j));
      count++;
    }
  }
  EXPECT_EQ(3, B.GetCols());
  EXPECT_EQ(3, B.GetRows());
}

TEST(Functions, EQUAL_MATRIX_1) {
  S21Matrix A(3, 5);
  S21Matrix B(3, 5);
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(Functions, EQUAL_MATRIX_2) {
  double arr[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  S21Matrix A(3, 5);
  A.FillMatrix(arr);
  S21Matrix B(3, 5);
  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(Functions, SUM_MATRIX_1) {
  double arr1[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  double arr2[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  S21Matrix A(3, 3);
  A.FillMatrix(arr1);
  S21Matrix B(3, 3);
  B.FillMatrix(arr2);
  A.SumMatrix(B);
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(arr1[count] + arr2[count], A(i, j));
      count++;
    }
  }
}

TEST(Functions, SUM_MATRIX_2) {
  double arr1[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  double arr2[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  S21Matrix A(3, 5);
  A.FillMatrix(arr1);
  S21Matrix B(3, 3);
  B.FillMatrix(arr2);
  EXPECT_THROW(A.SumMatrix(B), exception);
}

TEST(Functions, SUB_MATRIX_1) {
  double arr1[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  double arr2[] = {2, 4, 6, 0, 2, 4, 1, 3, 5};
  S21Matrix A(3, 3);
  A.FillMatrix(arr1);
  S21Matrix B(3, 3);
  B.FillMatrix(arr2);
  A.SubMatrix(B);
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(arr1[count] - arr2[count], A(i, j));
      count++;
    }
  }
}

TEST(Functions, SUB_MATRIX_2) {
  double arr1[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  double arr2[] = {2, 4, 6, 0, 2, 4, 1, 3, 5};
  S21Matrix A(3, 5);
  A.FillMatrix(arr1);
  S21Matrix B(3, 3);
  B.FillMatrix(arr2);
  EXPECT_THROW(A.SubMatrix(B), exception);
}

TEST(Functions, MUL_MATRIX_1) {
  S21Matrix A(2, 3);
  S21Matrix B(2, 3);
  EXPECT_THROW(A.MulMatrix(B), exception);
}

TEST(Functions, MUL_MATRIX_2) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  S21Matrix C(3, 3);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {5, 8, 1, 2, 3, 5};
  double arr3[] = {25, 39, 28, 53, 83, 52, 53, 83, 52};
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  C.FillMatrix(arr3);
  A.MulMatrix(B);
  EXPECT_EQ(3, A.GetCols());
  EXPECT_EQ(3, A.GetRows());
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(A(i, j), C(i, j));
    }
  }
}

TEST(Functions, MUL_NUMBER_1) {
  S21Matrix A(2, 3);
  S21Matrix B(2, 3);
  double arr1[] = {3, 5, -7, 9, -7, 8};
  double arr2[] = {6, 10, -14, 18, -14, 16};
  double num = 2.0;
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  A.MulNumber(num);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(A(i, j), B(i, j));
    }
  }
}

TEST(Operator, MUL_NUMBER_1) {
  S21Matrix A(2, 3);
  S21Matrix B(2, 3);
  // double arr1[] = {3, 5, -7, 9, -7, 8};
  // double arr2[] = {6, 10, -14, 18, -14, 16};
  double num = 2.0;
  A *num;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(A(i, j), B(i, j));
    }
  }
}

TEST(Operator, MUL_MATRIX_1) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  S21Matrix C(3, 3);
  S21Matrix res;
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {5, 8, 1, 2, 3, 5};
  double arr3[] = {25, 39, 28, 53, 83, 52, 53, 83, 52};
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  C.FillMatrix(arr3);
  res = A * B;
  EXPECT_EQ(3, res.GetCols());
  EXPECT_EQ(3, res.GetRows());
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(res(i, j), C(i, j));
    }
  }
}

TEST(Operator, SUM_MATRIX_1) {
  S21Matrix A(3, 2);
  S21Matrix B(3, 2);
  S21Matrix C;
  S21Matrix res(3, 2);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {5, 8, 1, 2, 3, 5};
  double arr3[] = {8, 13, 8, 11, 10, 14};
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  res.FillMatrix(arr3);
  C = A + B;
  for (int i = 0; i < res.GetRows(); i++) {
    for (int j = 0; j < res.GetCols(); j++) {
      EXPECT_EQ(C(i, j), res(i, j));
    }
  }
}

TEST(Operator, SUB_MATRIX_1) {
  S21Matrix A(3, 2);
  S21Matrix B(3, 2);
  S21Matrix C;
  S21Matrix res(3, 2);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {5, 8, 1, 2, 3, 5};
  double arr3[] = {-2, -3, 6, 7, 4, 4};
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  res.FillMatrix(arr3);
  C = A - B;
  for (int i = 0; i < res.GetRows(); i++) {
    for (int j = 0; j < res.GetCols(); j++) {
      EXPECT_EQ(C(i, j), res(i, j));
    }
  }
}

TEST(Operator, MUL_ASSIGN_MATRIX_1) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  S21Matrix C(3, 3);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {5, 8, 1, 2, 3, 5};
  double arr3[] = {25, 39, 28, 53, 83, 52, 53, 83, 52};
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  C.FillMatrix(arr3);
  A *= B;
  EXPECT_EQ(3, A.GetCols());
  EXPECT_EQ(3, A.GetRows());
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(A(i, j), C(i, j));
    }
  }
}

TEST(Operator, MUL_ASSIGN_MATRIX_2) {
  S21Matrix A(3, 2);
  double B = 2.;
  S21Matrix C(3, 2);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {6, 10, 14, 18, 14, 18};
  A.FillMatrix(arr1);
  C.FillMatrix(arr2);
  A *= B;
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      EXPECT_EQ(A(i, j), C(i, j));
    }
  }
}

TEST(Operator, SUM_ASSIGN_MATRIX_1) {
  S21Matrix A(3, 2);
  S21Matrix B(3, 2);
  S21Matrix res(3, 2);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {5, 8, 1, 2, 3, 5};
  double arr3[] = {8, 13, 8, 11, 10, 14};
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  res.FillMatrix(arr3);
  A += B;
  for (int i = 0; i < res.GetRows(); i++) {
    for (int j = 0; j < res.GetCols(); j++) {
      EXPECT_EQ(A(i, j), res(i, j));
    }
  }
}

TEST(Operator, SUB_ASSIGN_MATRIX_1) {
  S21Matrix A(3, 2);
  S21Matrix B(3, 2);
  S21Matrix res(3, 2);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {5, 8, 1, 2, 3, 5};
  double arr3[] = {-2, -3, 6, 7, 4, 4};
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  res.FillMatrix(arr3);
  A -= B;
  for (int i = 0; i < res.GetRows(); i++) {
    for (int j = 0; j < res.GetCols(); j++) {
      EXPECT_EQ(A(i, j), res(i, j));
    }
  }
}

TEST(Operator, EQ_MATRIX_1) {
  S21Matrix A(3, 2);
  S21Matrix B(3, 2);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  double arr2[] = {3, 5, 7, 9, 7, 9};
  A.FillMatrix(arr1);
  B.FillMatrix(arr2);
  EXPECT_TRUE(A == B);
}

TEST(Operator, INDEX_MATRIX_1) {
  S21Matrix A(3, 2);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  A.FillMatrix(arr1);
  for (int i = 0, count = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      EXPECT_EQ(A(i, j), arr1[count]);
      count++;
    }
  }
}

TEST(Operator, INDEX_MATRIX_2) {
  S21Matrix A(3, 2);
  double arr1[] = {3, 5, 7, 9, 7, 9};
  A.FillMatrix(arr1);
  EXPECT_THROW(A(2, 4), exception);
  EXPECT_THROW(A(4, 1), exception);
  EXPECT_THROW(A(-1, 1), exception);
  EXPECT_THROW(A(1, -1), exception);
}

TEST(Functions, TRANSPOSE_1) {
  double arr1[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  double arr2[] = {3, 1, 2, 5, 3, 4, 7, 5, 6};
  S21Matrix A(3, 3);
  A.FillMatrix(arr1);
  A.Transpose();
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(arr2[count], A(i, j));
      count++;
    }
  }
}

TEST(Functions, TRANSPOSE_2) {
  // double arr1[] = {3, 5, 7, 1, 3, 5, 2, 4, 6};
  // double arr2[] = {3, 1, 2, 5, 3, 4, 7, 5, 6};
  EXPECT_THROW(S21Matrix A(3, -2), exception);
}

TEST(Functions, CALC_COMPLEMENTS_1) {
  S21Matrix A(3, 3), correct_result(3, 3);
  double A_arr[] = {1., 2., 3., 0., 4., 2., 5., 2., 1.};
  double correct_result_arr[] = {0., 10., -20., 4., -14., 8., -8., -2., 4.};
  A.FillMatrix(A_arr);
  correct_result.FillMatrix(correct_result_arr);
  A.CalcComplements();
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      EXPECT_EQ(A(i, j), correct_result(i, j));
    }
  }
}

TEST(Functions, CALC_COMPLEMENTS_2) {
  S21Matrix A(2, 3);
  double A_arr[] = {1., 2., 3., 0., 4., 2.};
  A.FillMatrix(A_arr);
  EXPECT_THROW(A.CalcComplements(), exception);
}

TEST(Functions, CALC_COMPLEMENTS_3) {
  S21Matrix A(1, 1);
  double A_arr[] = {5.};
  A.FillMatrix(A_arr);
  A.CalcComplements();
  EXPECT_EQ(A(0, 0), 1);
}

TEST(Functions, DETERMINANT_1) {
  S21Matrix A(2, 3);
  double A_arr[] = {1., 2., 3., 0., 4., 2.};
  A.FillMatrix(A_arr);
  EXPECT_THROW(A.Determinant(), exception);
}

TEST(Functions, DETERMINANT_2) {
  S21Matrix A(3, 3);
  double A_arr[] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  A.FillMatrix(A_arr);
  A.Determinant();
  EXPECT_EQ(A.Determinant(), 0.);
}

TEST(Functions, DETERMINANT_3) {
  S21Matrix A(1, 1);
  double A_arr[] = {5.};
  A.FillMatrix(A_arr);
  A.Determinant();
  EXPECT_EQ(A(0, 0), 5.);
}

TEST(Functions, INVERSE_MATRIX_1) {
  S21Matrix A(3, 3);
  double A_arr[] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  A.FillMatrix(A_arr);
  EXPECT_THROW(A.InverseMatrix(), exception);
}

TEST(Functions, INVERSE_MATRIX_2) {
  S21Matrix A(3, 3), correct_result(3, 3);
  double A_arr[] = {2., 5., 7., 6., 3., 4., 5., -2., -3.};
  double correct_result_arr[] = {1., -1., 1., -38., 41., -34., 27., -29., 24.};
  A.FillMatrix(A_arr);
  correct_result.FillMatrix(correct_result_arr);
  A.InverseMatrix();
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      EXPECT_EQ(A(i, j), correct_result(i, j));
    }
  }
}

TEST(Functions, SET_COLS_1) {
  int rows = 3;
  int cols = 3;
  S21Matrix A(rows, cols);
  double A_arr[] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  A.FillMatrix(A_arr);
  A.SetCols(cols + 1);
  EXPECT_EQ(0, A(rows - 1, (cols + 1) - 1));
  EXPECT_THROW(A.SetCols(0), underflow_error);
}

TEST(Functions, SET_ROWS_1) {
  int rows = 3;
  int cols = 3;
  S21Matrix A(rows, cols);
  double A_arr[] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  A.FillMatrix(A_arr);
  A.SetRows(rows + 1);
  EXPECT_EQ(0, A((rows + 1) - 1, cols - 1));
  EXPECT_THROW(A.SetRows(0), underflow_error);
}

TEST(Supporting, CHECK_EQ_SIZE_MATRIX_1) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 3);
  EXPECT_FALSE(A.CheckEqSizeMatrix(B));
}

TEST(Supporting, CHECK_EQ_SIZE_MATRIX_2) {
  S21Matrix A(3, 2);
  S21Matrix B(3, 3);
  EXPECT_FALSE(A.CheckEqSizeMatrix(B));
}

TEST(Supporting, CHECK_EQ_SIZE_MATRIX_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  EXPECT_TRUE(A.CheckEqSizeMatrix(B));
}

TEST(Supporting, CHECK_EQ_SIZE_MATRIX_4) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);
  EXPECT_FALSE(A.CheckEqSizeMatrix(B));
}

TEST(MulNumOperator, TEST) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  S21Matrix tmp = b;
  b = b * 3;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }

  b = tmp;
  b = 3 * b;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }

  b = tmp;
  b *= 3;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }
}