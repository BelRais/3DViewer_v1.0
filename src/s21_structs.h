#ifndef S21_STRUCTS_H
#define S21_STRUCTS_H

#include "stdio.h"
#include "stdlib.h"

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct Matrix {  // Матрица, в которой индекс строки соответсвует
  double **matrix;       // индексу вершины
  int rows;  // Создаём на 1 размер больше, для того чтобы вершина
  int columns;  // которую мы первую считаем пошла в ряд с номером 1, а не 0
} matrix_t;

typedef struct data {
  int count_of_vertexes;  // кол-во вершин (при 1-ом чтении файла)
  int count_of_facets;  // кол-во полигонов (при 1-ом чтении файла)
  matrix_t matrix_3d;
  polygon_t *polygons;
} data_t;

struct data first_read(const char *name_of_file, struct data st);
struct data second_read(const char *name_of_file, struct data st);
int create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
struct data fill_polygon_2(char *str, struct data *st, int index_f);
struct data fill_polygon_1(char *str, struct data *st, int index_f);
struct data fill_matrix_v(char *str, struct data *st, int index_str);
struct data my_parser(const char *str);
double *fill_arr(const char *filename, struct data *st);
void s21_scale(matrix_t *A, double scale);
void s21_move_x(matrix_t *A, double a);
void s21_move_y(matrix_t *A, double a);
void s21_move_z(matrix_t *A, double a);
void s21_rotation_by_oy(matrix_t *A, double angle);
void s21_rotation_by_ox(matrix_t *A, double angle);
void s21_rotation_by_oz(matrix_t *A, double angle);
void s21_freeObjects(struct data *st);

#endif  // S21_STRUCTS_H
