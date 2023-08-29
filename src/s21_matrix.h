#ifndef SRC_S21_MATRIX_H
#define SRC_S21_MATRIX_H

#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result);

// очистка матриц
void s21_remove_matrix(matrix_t *A);

// сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// сложение и вычитание матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// умножение матрицы на число mult_number и умножение между собой
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// транспонирование
int s21_transpose(matrix_t *A, matrix_t *result);

// минор матрицы
int s21_calc_complements(matrix_t *A, matrix_t *result);
void s21_minor_matrix(matrix_t *src, matrix_t *dst, int i, int j);

// определитель матрицы
int s21_determinant(matrix_t *A, double *result);
double s21_det(matrix_t *A);
void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result);
int s21_check(matrix_t *matrix);

// обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H