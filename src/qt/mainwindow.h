#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include "ui_mainwindow.h"
#pragma once

extern "C" {
#include "../s21_structs.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_scale_clicked();

  void on_pushButton_OX_clicked();

  void on_pushButton_OY_clicked();

  void on_pushButton_OZ_clicked();

  void on_pushButton_ROX_clicked();

  void on_pushButton_ROY_clicked();

  void on_pushButton_ROZ_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
