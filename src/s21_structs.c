
#include "s21_structs.h"

#include <math.h>
#include <string.h>

struct data first_read(const char *name_of_file, struct data st) {
  int vertexes = 0, facets = 0;
  FILE *f = fopen(name_of_file, "r");
  if (f != NULL) {
    char str[512] = {};
    while (fgets(str, 512, f) != NULL) {
      if (str[0] == 'v' && str[1] == ' ') {
        vertexes++;
      }
      if (str[0] == 'f' && str[1] == ' ') {
        facets++;
      }
    }
    fclose(f);
  }
  // fclose(f);
  st.count_of_vertexes = vertexes;
  st.count_of_facets = facets;
  // printf("%d %d\n", st.count_of_facets, st.count_of_vertexes);
  return st;
}

struct data fill_polygon_1(char *str, struct data *st, int index_f) {
  // Начинаем считывать строку, начинающуюся на  f. Подсчитываем кол-во вершин и
  // заносим в polygons[i].numbers_of_vertexes_in_facets.
  int kol = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == ' ' && i + 1 < (int)strlen(str) && str[i + 1] >= '0' &&
        str[i + 1] <= '9') {
      kol++;
    }
  }
  st->polygons[index_f].numbers_of_vertexes_in_facets = kol;
  // printf("index_f = %d , numbers_of_vertexes_in_facets = %d\n", index_f, st
  // -> polygons[index_f].numbers_of_vertexes_in_facets);
  return *st;
}

struct data fill_polygon_2(char *str, struct data *st, int index_f) {
  // Теперь выделяем память для `polygons[i].vertexes`**,** равную
  //`polygons[i].numbers_of_vertexes_in_facets`. И эту же строку отправляем на
  // запись вершин в массив для которого мы только что выделили память.
  st->polygons[index_f].vertexes = (int *)malloc(
      (st->polygons[index_f].numbers_of_vertexes_in_facets) * sizeof(int));
  // printf("numbers_of_vertexes_in_facets = %d\n", st ->
  // polygons[index_f].numbers_of_vertexes_in_facets);
  int k = 0;
  int index = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    char number[128] = "";
    if (str[i] >= '0' && str[i] <= '9') {
      while (i < (int)strlen(str) && str[i] != '/' && str[i] != ' ') {
        number[k++] = str[i++];
      }
      if (i < (int)strlen(str) && str[i] == '/') {
        while (str[i] != ' ') i++;
      }
      number[k] = '\0';
      int num_int = atoi(number);
      k = 0;
      st->polygons[index_f].vertexes[index++] = num_int;
    }
  }
  return *st;
}

struct data fill_matrix_v(char *str, struct data *st, int index_str) {
  int k = 0;
  int koord = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    char number[512] = "";
    while (i < (int)strlen(str) && str[i] != ' ' &&
           ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' ||
            str[i] == '-' || str[i] == '+')) {
      number[k++] = str[i++];
    }
    if (i == (int)strlen(str) - 1 || (str[i] == ' ' && k != 0)) {
      number[k] = '\0';
      k = 0;
      double a = atof(number);
      st->matrix_3d.matrix[index_str][koord++] = a;
    }
  }
  return *st;
}
//   //number[k] = '\0';
//   // double a = atof(number);
//   // st->matrix_3d.matrix[index_str][koord++] = a;

//   return *st;
// }
struct data second_read(const char *name_of_file, struct data st) {
  int err = create_matrix(st.count_of_vertexes + 1, 3, &st.matrix_3d);
  if (err == 0) {
    st.polygons =
        (polygon_t *)malloc((st.count_of_facets + 1) * sizeof(polygon_t));
    // printf("yasdes");
    // st.polygons[866].numbers_of_vertexes_in_facets = 5;
    // printf("yatut");
    FILE *f = fopen(name_of_file, "r");
    if (f != NULL) {
      int index_v = 1;
      int index_f = 1;
      char str[2056] = {};
      // printf("INDEX = %d\n", index_f);
      while (fgets(str, 2056, f) != NULL) {
        // printf("%s\n", str);
        if (str[0] == 'v' &&
            str[1] == ' ') {  // если вершина, то мы должны заполнить матрицу
                              // координатами этой вершины с индексом index_str
          st = fill_matrix_v(str, &st, index_v);
          index_v++;
        } else if (str[0] == 'f' && str[1] == ' ') {  // если полигон, то :
          st = fill_polygon_1(
              str, &st,
              index_f);  // Первая функция необходима для подсчета кол-ва
                         // вершин, которые необходимо соединить.
          st = fill_polygon_2(
              str, &st,
              index_f);  // записывает вершины в массив polygons[i].vertexes
          index_f++;
        }
      }
      // printf("INDEX = %d\n", index_f);
      fclose(f);
    }
  }
  return st;
}

int create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    err = 1;
  } else {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (!result->matrix) err = 1;
  }
  if (err == 0) {
    for (int i = 0; i < rows && !err; i++) {
      result->matrix[i] = malloc(columns * sizeof(double));
      if (!result->matrix[i]) {
        err = 1;
        for (int j = 0; j < i; j++) free(result->matrix[j]);
        free(result->matrix);
      }
    }
  }
  if (err == 0) {
    result->rows = rows;
    result->columns = columns;
  }
  return err;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

struct data my_parser(const char *filename) {
  struct data st = {0};
  st = first_read(filename, st);
  st = second_read(filename, st);
  return st;
}

void s21_scale(matrix_t *A, double scale) {
  if (scale != 0.0) {
    for (int i = 1; i < A->rows && scale > 0; i++) {
      A->matrix[i][0] *= scale;
      A->matrix[i][1] *= scale;
      A->matrix[i][2] *= scale;
    }
    if (scale < 0) {
      scale *= -1;
      for (int i = 1; i < A->rows; i++) {
        A->matrix[i][0] /= scale;
        A->matrix[i][1] /= scale;
        A->matrix[i][2] /= scale;
      }
    }
  }
}
void s21_move_x(matrix_t *A, double a) {
  if (a != 0.0) {
    for (int i = 1; i < A->rows; i++) {
      A->matrix[i][0] += a;
    }
  }
}
void s21_move_y(matrix_t *A, double a) {
  if (a != 0.0) {
    for (int i = 1; i < A->rows; i++) {
      A->matrix[i][1] += a;
    }
  }
}
void s21_move_z(matrix_t *A, double a) {
  if (a != 0.0) {
    for (int i = 1; i < A->rows; i++) {
      A->matrix[i][2] += a;
    }
  }
}

void s21_rotation_by_ox(matrix_t *A, double angle) {
  for (int i = 1; i < A->rows && angle != 0.0; i++) {
    double temp_y = A->matrix[i][1];
    double temp_z = A->matrix[i][2];
    A->matrix[i][1] = cos(angle) * temp_y + sin(angle) * temp_z;
    A->matrix[i][2] = -sin(angle) * temp_y + cos(angle) * temp_z;
  }
}
void s21_rotation_by_oy(matrix_t *A, double angle) {
  for (int i = 1; i < A->rows && angle != 0.0; i++) {
    double temp_x = A->matrix[i][0];
    double temp_z = A->matrix[i][2];
    A->matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_z;
    A->matrix[i][2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}
void s21_rotation_by_oz(matrix_t *A, double angle) {
  for (int i = 1; i < A->rows && angle != 0.0; i++) {
    double temp_x = A->matrix[i][0];
    double temp_y = A->matrix[i][1];
    A->matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_y;
    A->matrix[i][1] = -sin(angle) * temp_x + cos(angle) * temp_y;
  }
}
void s21_freeObjects(struct data *st) {
  s21_remove_matrix(&st->matrix_3d);
  for (int i = 1; i <= st->count_of_facets; i++) {
    free(st->polygons[i].vertexes);
  }
  free(st->polygons);
}
// int main() {
// struct data st;
// st = my_parser("city.obj");
// printf("%d %d\n", st.count_of_facets, st.count_of_vertexes);
// s21_freeObjects(&st);
// }
// int main() {
//   struct data st;
//   st = my_parser("piramid.obj");
//   for (int i = 0; i < st.matrix_3d.rows; i++) {
//     for (int j = 0; j < st.matrix_3d.columns; j++) {
//       printf("%f ", st.matrix_3d.matrix[i][j]);
//     }
//     printf("\n");
//   }
// }
