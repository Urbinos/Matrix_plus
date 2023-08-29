#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int fails = 0;
  result->rows = rows;
  result->columns = columns;

  if (rows < 1 || columns < 1) {
    fails = 1;
    result->matrix = NULL;
  } else {
    double **array_pointer = calloc(rows, sizeof(double *));
    double *array_value = calloc(rows * columns, sizeof(double));
    if (array_pointer != NULL && array_value != NULL) {
      for (int i = 0; i < rows; i++) {
        array_pointer[i] = array_value + columns * i;
      }
      result->matrix = array_pointer;
    } else {
      fails = 1;
    }
  }
  return fails;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    if (A->rows) {
      A->rows = 0;
    }
    if (A->columns) {
      A->columns = 0;
    }
    if (A->matrix[0]) {
      free(A->matrix[0]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int fails = SUCCESS;
  if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL &&
      A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          fails = FAILURE;
        }
      }
    }
  } else {
    fails = FAILURE;
  }
  return fails;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int fails = 0;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns && A != NULL &&
        B != NULL) {
      int rows = A->rows;
      int columns = A->columns;

      fails = s21_create_matrix(rows, columns, result);
      if (fails == 0) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    } else {
      fails = 2;
    }
  } else {
    fails = 1;
  }
  return fails;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int fails = 0;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns && A != NULL &&
        B != NULL) {
      int rows = A->rows;
      int columns = A->columns;
      fails = s21_create_matrix(rows, columns, result);
      if (fails == 0) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    } else {
      fails = 2;
    }
  } else {
    fails = 1;
  }
  return fails;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int fails = 0;
  if (A->matrix == NULL) {
    fails = 1;
  }
  if (fails == 0) {
    fails = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    result->matrix = NULL;
  }
  return fails;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int fails = 0;
  if (A->matrix != NULL && A->rows > 0 && A->columns > 0 && B->matrix != NULL &&
      B->rows > 0 && B->columns > 0) {
    if (A->columns == B->rows) {
      fails = s21_create_matrix(A->rows, B->columns, result);

      if (fails == 0)
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < B->columns; j++)
            for (int k = 0; k < A->columns; k++)
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
    } else {
      fails = 2;
    }

  } else {
    fails = 1;
  }
  return fails;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int fails = 0;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    fails = s21_create_matrix(A->columns, A->rows, result);
    if (fails == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    fails = 1;
  }
  return fails;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int fails = 0;
  if (s21_check(A) == 0) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->columns, A->rows, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor_matrix = {0};
          double det = 0;
          s21_create_matrix(A->columns - 1, A->rows - 1, &minor_matrix);
          s21_get_matrix(i, j, A, &minor_matrix);
          s21_determinant(&minor_matrix, &det);
          result->matrix[i][j] = pow(-1, (i + j)) * det;
          s21_remove_matrix(&minor_matrix);
        }
      }
    } else {
      fails = 2;
    }
  } else {
    fails = 1;
  }
  return fails;
}

void s21_minor_matrix(matrix_t *src, matrix_t *dst, int i, int j) {
  int maitrix_size = src->columns;
  int minor_size = dst->columns;
  int minor_matrix_i = 0;
  int minor_matrix_j = 0;
  for (int k = 0; k < maitrix_size; k++) {
    for (int l = 0; l < maitrix_size; l++) {
      if (k != i && l != j) {
        dst->matrix[minor_matrix_i][minor_matrix_j] = src->matrix[k][l];

        if (minor_matrix_j + 1 != minor_size) {
          minor_matrix_j++;
        } else {
          minor_matrix_i++;
          minor_matrix_j = 0;
        }
      }
    }
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int fails = 0;
  *result = 0.0;
  if (s21_check(A) == 0) {
    if (A->columns == A->rows) {
      *result = s21_det(A);
    } else {
      fails = 2;
    }
  } else {
    fails = 1;
  }
  return fails;
}

double s21_det(matrix_t *A) {
  double fails = 0.0;
  if (A->rows == 1) {
    fails = A->matrix[0][0];
  } else {
    matrix_t dst = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &dst);
    for (int i = 0; i < A->columns; i++) {
      s21_get_matrix(0, i, A, &dst);
      if (i % 2) {
        fails -= A->matrix[0][i] * s21_det(&dst);
      } else {
        fails += A->matrix[0][i] * s21_det(&dst);
      }
    }
    s21_remove_matrix(&dst);
  }
  return fails;
}

void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result) {
  int m_row = 0;
  int m_col = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i != row) {
      m_col = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != col) {
          result->matrix[m_row][m_col] = A->matrix[i][j];
          m_col++;
        }
      }
      m_row++;
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int fails = 0;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->columns == A->rows) {
      double det = 0;
      s21_determinant(A, &det);
      if (fabs(det) > 1e-7) {
        matrix_t buff_1 = {NULL, 0, 0};
        matrix_t buff_2 = {NULL, 0, 0};
        s21_calc_complements(A, &buff_1);
        s21_transpose(&buff_1, &buff_2);

        s21_mult_number(&buff_2, 1.0 / det, result);

        s21_remove_matrix(&buff_1);
        s21_remove_matrix(&buff_2);
      } else {
        fails = 2;
      }
    } else {
      fails = 2;
    }
  } else {
    fails = 1;
  }
  return fails;
}

int s21_check(matrix_t *matrix) {
  int res = 0;
  if (matrix == NULL || matrix->matrix == NULL || matrix->rows <= 0 ||
      matrix->columns <= 0) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}
