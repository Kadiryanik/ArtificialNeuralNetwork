/**
 * \file
 *        Simple coordinate box widget.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#ifndef COORDINATEBOX_H
#define COORDINATEBOX_H

#include <QWidget>
#include <QLine>

/*---------------------------------------------------------------------------*/
#define COORDINATE_BOX_UPLIMIT_X 400
#define COORDINATE_BOX_UPLIMIT_Y 400

/*---------------------------------------------------------------------------*/
class MainWindow;

/*---------------------------------------------------------------------------*/
class CoordinateBox : public QWidget
{
  Q_OBJECT

public:
  explicit CoordinateBox(QWidget *parent = nullptr);

  int zoomVal;
  void paintEvent(QPaintEvent * event);
  void mousePressEvent(QMouseEvent* event);
private:
  MainWindow *parent;
};

#endif // COORDINATEBOX_H
