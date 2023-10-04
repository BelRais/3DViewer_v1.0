#include <check.h>
#include <stdio.h>

#include "s21_structs.h"
/*
void fill_matrix (matrix_t *matr) {
  matr->matrix[1][0] = -1.0;
  matr->matrix[1][1] = 0.0;
  matr->matrix[1][2] = -1.000000;
  matr->matrix[2][0] = 1.0;
  matr->matrix[2][1] = 0.000000;
  matr->matrix[2][2] = -1.000000;
  matr->matrix[3][0] = 1.000000;
  matr->matrix[3][1] = 0.0;
  matr->matrix[3][2] = 1.000000;
  matr->matrix[4][0] = -1.000000;
  matr->matrix[4][1] = 0.0;
  matr->matrix[4][2] = 1.000000;
  matr->matrix[5][0] = 0.000000;
  matr->matrix[5][1] = 1.0;
  matr->matrix[5][2] = 0.0;
}
*/

START_TEST(result_test_for_move_x) {
  struct data st = my_parser("piramid.obj");
  // s21_rotation_by_ox(&st.matrix_3d, 1);
  // s21_rotation_by_oy(&st.matrix_3d, 1);
  // s21_rotation_by_oz(&st.matrix_3d, 1);
  // s21_scale(&st.matrix_3d, 1.1);
  s21_move_x(&st.matrix_3d, 1.0);
  // s21_move_y(&st.matrix_3d, 1);
  // s21_move_z(&st.matrix_3d, 1);

  // printf("%f\n", st.matrix_3d.matrix[1][0]);

  ck_assert_double_eq(st.matrix_3d.matrix[1][0], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[2][0], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[3][0], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][0], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[5][0], 1.0);
  s21_freeObjects(&st);
}
END_TEST

START_TEST(result_test_for_move_y) {
  struct data st = my_parser("piramid.obj");
  s21_move_y(&st.matrix_3d, 1);

  // printf("%f\n", st.matrix_3d.matrix[1][1]);
  ck_assert_double_eq(st.matrix_3d.matrix[1][1], 1.0);
  ck_assert_double_eq(st.matrix_3d.matrix[2][1], 1.0);
  ck_assert_double_eq(st.matrix_3d.matrix[3][1], 1.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][1], 1.0);
  ck_assert_double_eq(st.matrix_3d.matrix[5][1], 2.0);
  s21_freeObjects(&st);
}
END_TEST

START_TEST(result_test_for_move_z) {
  struct data st = my_parser("piramid.obj");
  s21_move_z(&st.matrix_3d, 1);
  // printf("%f\n", st.matrix_3d.matrix[1][2]);
  ck_assert_double_eq(st.matrix_3d.matrix[1][2], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[2][2], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[3][2], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][2], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[5][2], 1.0);
  s21_freeObjects(&st);
}
END_TEST

START_TEST(result_test_for_rotation_by_ox) {
  struct data st = my_parser("piramid.obj");
  s21_rotation_by_ox(&st.matrix_3d, 0.785398163 * 2);

  /*-----------------------------for_x------------------------------*/
  ck_assert_double_eq(st.matrix_3d.matrix[1][0], -1.0);
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][0]), roundf(1.0));
  ck_assert_double_eq(st.matrix_3d.matrix[3][0], 1.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][0], -1.0);
  ck_assert_double_eq(st.matrix_3d.matrix[5][0], 0.0);
  /*-----------------------------for_y------------------------------*/
  ck_assert_double_eq(st.matrix_3d.matrix[1][1],
                      -1.0);  // 0.785398163 это в радианах!!!!!!!!!!!!!!!!
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][1]), roundf(-1.0));
  ck_assert_double_eq(st.matrix_3d.matrix[3][1], 1.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][1], 1.0);
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[5][1]), roundf(0.0));
  /*-----------------------------for_z------------------------------*/
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[1][2]), roundf(0.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][2]), roundf(0.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[3][2]), roundf(0.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[4][2]), roundf(0.0));
  ck_assert_double_eq(st.matrix_3d.matrix[5][2], -1.0);

  s21_freeObjects(&st);
}
END_TEST

START_TEST(result_test_for_rotation_by_oy) {
  struct data st = my_parser("piramid.obj");
  s21_rotation_by_oy(&st.matrix_3d, 0.785398163 * 2);
  /*-----------------------------for_x------------------------------*/
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[1][0]), roundf(-1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][0]), roundf(-1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[3][0]), roundf(1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[4][0]), roundf(1.0));
  ck_assert_double_eq(st.matrix_3d.matrix[5][0], 0.0);
  /*-----------------------------for_y------------------------------*/
  ck_assert_double_eq(
      roundf(st.matrix_3d.matrix[1][1]),
      roundf(0.0));  // 0.785398163 это в радианах!!!!!!!!!!!!!!!!
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][1]), roundf(0.0));
  ck_assert_double_eq(st.matrix_3d.matrix[3][1], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][1], 0.0);
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[5][1]), roundf(1.0));
  /*-----------------------------for_z------------------------------*/
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[1][2]), roundf(1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][2]), roundf(-1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[3][2]), roundf(-1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[4][2]), roundf(1.0));
  ck_assert_double_eq(st.matrix_3d.matrix[5][2], 0.0);

  s21_freeObjects(&st);
}
END_TEST

START_TEST(result_test_for_rotation_by_oz) {
  struct data st = my_parser("piramid.obj");

  s21_rotation_by_oz(&st.matrix_3d, 0.785398163 * 2);

  /*-----------------------------for_x------------------------------*/
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[1][0]), roundf(-0.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][0]), roundf(0.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[3][0]), roundf(0.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[4][0]), roundf(0.0));
  ck_assert_double_eq(st.matrix_3d.matrix[5][0], 1.0);
  /*-----------------------------for_y------------------------------*/
  ck_assert_double_eq(
      roundf(st.matrix_3d.matrix[1][1]),
      roundf(1.0));  // 0.785398163 это в радианах!!!!!!!!!!!!!!!!
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][1]), roundf(-1.0));
  ck_assert_double_eq(st.matrix_3d.matrix[3][1], -1.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][1], 1.0);
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[5][1]), roundf(0.0));
  /*-----------------------------for_z------------------------------*/
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[1][2]), roundf(-1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[2][2]), roundf(-1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[3][2]), roundf(1.0));
  ck_assert_double_eq(roundf(st.matrix_3d.matrix[4][2]), roundf(1.0));
  ck_assert_double_eq(st.matrix_3d.matrix[5][2], 0.0);

  s21_freeObjects(&st);
}
END_TEST

START_TEST(result_test_for_s21_scale) {
  struct data st = my_parser("piramid.obj");
  s21_scale(&st.matrix_3d, 2);
  ck_assert_double_eq(st.matrix_3d.matrix[1][0], -2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[1][1], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[1][2], -2.0);  //
  ck_assert_double_eq(st.matrix_3d.matrix[2][0], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[2][1], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[2][2], -2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[3][0], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[3][1], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[3][2], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][0], -2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][1], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[4][2], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[5][0], 0.0);
  ck_assert_double_eq(st.matrix_3d.matrix[5][1], 2.0);
  ck_assert_double_eq(st.matrix_3d.matrix[5][2], 0.0);
  s21_freeObjects(&st);
}
END_TEST

int main(void) {
  Suite *s21_suite_3D = suite_create("s21_3D_test");
  TCase *s21_TCase_3D = tcase_create("s21_3D_test");
  SRunner *s21_srunner_3D = srunner_create(s21_suite_3D);
  int kra;

  suite_add_tcase(s21_suite_3D, s21_TCase_3D);
  tcase_add_test(s21_TCase_3D, result_test_for_move_x);
  tcase_add_test(s21_TCase_3D, result_test_for_move_y);
  tcase_add_test(s21_TCase_3D, result_test_for_move_z);
  tcase_add_test(s21_TCase_3D, result_test_for_rotation_by_ox);
  tcase_add_test(s21_TCase_3D, result_test_for_s21_scale);
  tcase_add_test(s21_TCase_3D, result_test_for_rotation_by_oy);
  tcase_add_test(s21_TCase_3D, result_test_for_rotation_by_oz);

  srunner_run_all(s21_srunner_3D, CK_ENV);
  kra = srunner_ntests_failed(s21_srunner_3D);
  srunner_free(s21_srunner_3D);

  return kra == 0 ? 0 : 1;
}
