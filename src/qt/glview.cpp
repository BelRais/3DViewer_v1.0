#include "glview.h"
// #include "ui_mainwindow.h"
#include <QApplication>

#include "string.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget{parent}  //    , ui(new Ui::MainWindow)
{}

void glView::initializeGL() {
  glClearColor(0, 1, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void glView::paintGL() {
  glClearColor(0, 1, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -7);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  glRotatef(zRot, 0, 0, 1);
  draw();
}

void glView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLfloat x = (GLfloat)w / h;
  glFrustum(-x, x, -1.0, 1.0, 0.2, 10000000000);
}

void glView::draw() {
  int sum = 0;
  for (int k = 1; k <= st.count_of_facets; k++) {
    sum += st.polygons[k].numbers_of_vertexes_in_facets * 2;
  }
  double *coord = (double *)calloc((sum * 3), sizeof(double));
  int p = 0;
  for (int k = 1; k <= st.count_of_facets; k++) {
    int kol = 0;
    for (int i = 0; i < st.polygons[k].numbers_of_vertexes_in_facets; i++) {
      kol++;
      coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[i]][0];
      coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[i]][1];
      coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[i]][2];
      if (kol % 2 == 0 &&
          i != st.polygons[k].numbers_of_vertexes_in_facets - 1) {
        kol = 0;
        i--;
      } else if (i == st.polygons[k].numbers_of_vertexes_in_facets - 1) {
        coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[i]][0];
        coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[i]][1];
        coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[i]][2];

        coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[0]][0];
        coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[0]][1];
        coord[p++] = st.matrix_3d.matrix[st.polygons[k].vertexes[0]][2];
      }
    }
  }
  glVertexPointer(3, GL_DOUBLE, 0, coord);
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor3f(1, 1, 1);
  glDrawArrays(GL_LINES, 0, sum);
  glDisableClientState(GL_VERTEX_ARRAY);
  free(coord);
}

void glView::deleteObj() {
  s21_remove_matrix(&st.matrix_3d);
  for (int i = 1; i <= st.count_of_facets; i++) {
    free(st.polygons[i].vertexes);
  }
  free(st.polygons);
}
void glView::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }
void glView::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
glView::~glView() {
  //    delete ui;
}
