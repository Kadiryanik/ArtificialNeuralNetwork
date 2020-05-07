/**
 * \file
 *        Simple form gui.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AnnMatrix.h"

#include <QMessageBox>

/*---------------------------------------------------------------------------*/
/*---------------------------Public-Functions--------------------------------*/
/*---------------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow){
  ui->setupUi(this);
  this->setWindowTitle("MultiLayer Network Classifier");

  ui->lineEditClass->setText("2");

  coordinateBox = new CoordinateBox(this);
  ui->verticalLayoutCoorBox->addWidget(coordinateBox);
  ui->horizontalSliderZoom->setValue(1);
  coordinateBox->zoomVal = 1;
}

/*---------------------------------------------------------------------------*/
MainWindow::~MainWindow(){
  delete ui;
  delete coordinateBox;
  if(ann != nullptr) delete ann;
}

/*---------------------------------------------------------------------------*/
void MainWindow::error(MainWindow *ptr, QString strTitle, QString strText){
  QMessageBox msgBox(ptr);
  msgBox.setWindowTitle(strTitle);
  msgBox.setText(strText);
  msgBox.exec();
}

/*---------------------------------------------------------------------------*/
QListWidget* MainWindow::getListWidget(){
    return ui->listWidget;
}

/*---------------------------------------------------------------------------*/
CoordinateBox* MainWindow::getCoordinateBox(){
  return coordinateBox;
}

/*---------------------------------------------------------------------------*/
Ann* MainWindow::getAnn(){
    return ann;
}

/*---------------------------------------------------------------------------*/
/*----------------------------Static-Functions-------------------------------*/
/*---------------------------------------------------------------------------*/
static QVector<QColor> randColors(int count){
  QVector<QColor> colors;
  float currentHue = 0.0;
  for (int i = 0; i < count; i++){
    colors.push_back( QColor::fromHslF(currentHue, 1.0, 0.5) );
    currentHue += 0.618033988749895f;
    currentHue = std::fmod(currentHue, 1.0f);
  }
  return colors;
}

/*---------------------------------------------------------------------------*/
/*----------------------------------Slots------------------------------------*/
/*---------------------------------------------------------------------------*/
void MainWindow::on_pushButtonProcess_clicked(){
  ui->horizontalSliderZoom->setValue(50);

  if(ann != nullptr && ann->train()){
    // repaint for test results
    coordinateBox->repaint();
    ui->horizontalSliderZoom->setValue(1);
    error(this, "Warn!", "Succeed!");
  } else{
    error(this, "Warn!", "Failed!");
  }
}

/*---------------------------------------------------------------------------*/
void MainWindow::on_pushButtonReset_clicked(){
  if(ann != nullptr){
    delete ann;
    ann = nullptr;
  }

  coordinateBox->repaint();
  ui->horizontalSliderZoom->setValue(1);

  // clear list
  ui->listWidget->clear();
}

/*---------------------------------------------------------------------------*/
void MainWindow::on_pushButtonStorePointsReset_clicked(){
  if(ann != nullptr){
    ann->storePointsAndReset();
    coordinateBox->repaint();
    ui->horizontalSliderZoom->setValue(1);
  }
}

/*---------------------------------------------------------------------------*/
void MainWindow::on_pushButtonDeleteLastPoint_clicked(){
  if(ann != nullptr){
    ann->deleteLastPoint();
    coordinateBox->repaint();
  }
}

/*---------------------------------------------------------------------------*/
void MainWindow::on_pushButtonGenerateClasses_clicked(){
  int classNumber = ui->lineEditClass->text().toInt();
  if(classNumber > 1){
    colors = randColors(classNumber);

    // clear points and coordinate box
    on_pushButtonReset_clicked(); // little hack here calling slot

    // clear list
    ui->listWidget->clear();

    for(int i = 0; i < classNumber; i++){
      QListWidgetItem *item = new QListWidgetItem(QString("Class-%1").arg(i));
      item->setForeground(colors[i]);

      ui->listWidget->addItem(item);
    }

    ann = new Ann(classNumber, coordinateBox);
  } else{
    error(this, "Total Class Number Error!", "It's value have to bigger than 1!");
  }
}

/*---------------------------------------------------------------------------*/
void MainWindow::on_horizontalSliderZoom_valueChanged(int value){
  coordinateBox->zoomVal = value;
  coordinateBox->repaint();
}
