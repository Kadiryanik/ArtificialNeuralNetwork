/**
 * \file
 *        Simple form gui.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CoordinateBox.h"
#include "Ann.h"

#include <QMainWindow>
#include <QListWidgetItem>

/*---------------------------------------------------------------------------*/
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*---------------------------------------------------------------------------*/
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  QVector<QColor> colors;

  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void error(MainWindow *ptr, QString strTitle, QString strText);
  QListWidget* getListWidget();
  CoordinateBox* getCoordinateBox();
  Ann* getAnn();
private:
  Ui::MainWindow *ui;
  CoordinateBox *coordinateBox;
  Ann *ann;

private slots:
  void on_pushButtonReset_clicked();
  void on_pushButtonProcess_clicked();
  void on_pushButtonStorePointsReset_clicked();
  void on_pushButtonDeleteLastPoint_clicked();
  void on_pushButtonGenerateClasses_clicked();
  void on_horizontalSliderZoom_valueChanged(int value);
};
#endif // MAINWINDOW_H
