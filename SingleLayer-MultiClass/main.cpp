/**
 * \file
 *        Simple main for start application.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#include "mainwindow.h"

#include <QApplication>

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[]){
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
