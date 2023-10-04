#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

extern "C" {
#include "../s21_structs.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class glView;
}
QT_END_NAMESPACE

class glView : public QOpenGLWidget {
  Q_OBJECT
 public:
  struct data st;
  QString catalog_of_file;
  float xRot, yRot, zRot;
  QPoint mPos;
  QTimer tmr;
  int space_out;
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  explicit glView(QWidget *parent = nullptr);
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  glView(QOpenGLWidget *parent = nullptr);
  void draw();
  void deleteObj();
  ~glView();

 signals:
};

#endif  // GLVIEW_H
