#define GL_SILENCE_DEPRECATION
#include "mainwindow.h"

#include <locale.h>

#include <QColorDialog>
#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  //    qDebug("Запуск приложения");
  //    ui->GLwidget->space_out = 0;
  ui->setupUi(this);
  ui->GLwidget->space_out = 0;
}

MainWindow::~MainWindow() {
  if (ui->GLwidget->space_out == 1) {
    ui->GLwidget->deleteObj();
  }
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  ui->GLwidget->catalog_of_file =
      QFileDialog::getOpenFileName(0, "krakra.obj", PRO_FILE_PWD, "*.obj");
  QString filePath = ui->GLwidget->catalog_of_file;
  QFileInfo fileInfo(filePath);
  QString pathWithoutFile = fileInfo.path();
  QString fileName = fileInfo.fileName();
  ui->label_location_show->setText(pathWithoutFile);
  ui->label_file_name_show->setText(fileName);
  QByteArray str = ui->GLwidget->catalog_of_file.toLocal8Bit();
  char *filepath = str.data();
  if (ui->GLwidget->space_out == 1) {
    ui->GLwidget->deleteObj();
    ui->GLwidget->space_out = 0;
  }
  ui->GLwidget->st = my_parser(filepath);
  ui->GLwidget->space_out = 1;
  ui->label_poligons_show->setText(
      QString::number(ui->GLwidget->st.count_of_facets));
  ui->label_vertexes_show->setText(
      QString::number(ui->GLwidget->st.count_of_vertexes));
}

void MainWindow::on_pushButton_scale_clicked() {
  bool ok = true;
  double number = ui->label_fscale_show->text().toDouble(&ok);
  if (ok) {
    s21_scale(&ui->GLwidget->st.matrix_3d, number);
    ui->GLwidget->update();
  } else {
    qDebug("Неверное значение");
  }
}

void MainWindow::on_pushButton_OX_clicked() {
  bool ok = true;
  double number = ui->label_OX_show->text().toDouble(&ok);
  if (ok) {
    s21_move_x(&ui->GLwidget->st.matrix_3d, number);
    ui->GLwidget->update();
  } else {
    qDebug("Неверное значение");
  }
}

void MainWindow::on_pushButton_OY_clicked() {
  bool ok = true;
  double number = ui->label_OY_show->text().toDouble(&ok);
  if (ok) {
    s21_move_y(&ui->GLwidget->st.matrix_3d, number);
    ui->GLwidget->update();
  } else {
    qDebug("Неверное значение");
  }
}

void MainWindow::on_pushButton_OZ_clicked() {
  bool ok = true;
  double number = ui->label_OZ_show->text().toDouble(&ok);
  if (ok) {
    s21_move_z(&ui->GLwidget->st.matrix_3d, number);
    ui->GLwidget->update();
  } else {
    qDebug("Неверное значение");
  }
}

void MainWindow::on_pushButton_ROX_clicked() {
  bool ok = true;
  double number = ui->label_ROX_show->text().toDouble(&ok);
  if (ok) {
    s21_rotation_by_ox(&ui->GLwidget->st.matrix_3d, number);
    ui->GLwidget->update();
  } else {
    qDebug("Неверное значение");
  }
}

void MainWindow::on_pushButton_ROY_clicked() {
  bool ok = true;
  double number = ui->label_ROY_show->text().toDouble(&ok);
  if (ok) {
    s21_rotation_by_oy(&ui->GLwidget->st.matrix_3d, number);
    ui->GLwidget->update();
  } else {
    qDebug("Неверное значение");
  }
}

void MainWindow::on_pushButton_ROZ_clicked() {
  bool ok = true;
  double number = ui->label_ROZ_show->text().toDouble(&ok);
  if (ok) {
    s21_rotation_by_oz(&ui->GLwidget->st.matrix_3d, number);
    ui->GLwidget->update();
  } else {
    qDebug("Неверное значение");
  }
}

void MainWindow::on_pushButton_2_clicked() {
  QString filePath = ui->GLwidget->catalog_of_file;
  QByteArray str = ui->GLwidget->catalog_of_file.toLocal8Bit();
  char *filepath = str.data();
  ui->GLwidget->st = my_parser(filepath);
  ui->GLwidget->update();
}
