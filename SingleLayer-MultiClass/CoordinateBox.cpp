/**
 * \file
 *        Simple coordinate box widget.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#include "CoordinateBox.h"
#include "mainwindow.h"

#include <QElapsedTimer>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

/*---------------------------------------------------------------------------*/
#define POINT_PLUS_SIZE    3
#define POINT_PLUS_WIDTH   2
#define WEIGHT_LINES_WIDTH 2

/*---------------------------------------------------------------------------*/
CoordinateBox::CoordinateBox(QWidget *parent) : QWidget(parent){
  this->parent = (MainWindow *)parent;

  QPalette Pal(palette());
  Pal.setColor(QPalette::Background, Qt::white);

  setPalette(Pal);
  setAutoFillBackground(true);

  resize(COORDINATE_BOX_UPLIMIT_X, COORDINATE_BOX_UPLIMIT_Y);
  show();
}

/*---------------------------------------------------------------------------*/
void CoordinateBox::paintEvent(QPaintEvent *event){
  (void)event;
  QPainter painter(this);

  // clear the coordinate box
  painter.fillRect(0, 0, COORDINATE_BOX_UPLIMIT_X, COORDINATE_BOX_UPLIMIT_Y, \
    QBrush(Qt::white));

  // draw x = 0 and y = 0 lines
  painter.drawLine(COORDINATE_BOX_UPLIMIT_X / 2, 0, \
    COORDINATE_BOX_UPLIMIT_X / 2, COORDINATE_BOX_UPLIMIT_Y);
  painter.drawLine(0, COORDINATE_BOX_UPLIMIT_Y / 2, \
    COORDINATE_BOX_UPLIMIT_X, COORDINATE_BOX_UPLIMIT_Y / 2);

  painter.setRenderHint(QPainter::Antialiasing);
  painter.save();

  Ann *ann = parent->getAnn();
  if(ann != nullptr){
    AnnPoint* p = ann->getPointList()->getPoints();
    while ((p = p->next()) != nullptr){
      QPen pen(parent->colors[p->classId()], POINT_PLUS_WIDTH);
      painter.setPen(pen);

      QPoint pos(p->x() * zoomVal + (COORDINATE_BOX_UPLIMIT_X / 2), \
        (COORDINATE_BOX_UPLIMIT_Y / 2) - p->y() * zoomVal);

      painter.drawLine(pos.x() - POINT_PLUS_SIZE, pos.y(),
               pos.x() + POINT_PLUS_SIZE, pos.y());

      painter.drawLine(pos.x(), pos.y() - POINT_PLUS_SIZE,
               pos.x(), pos.y() + POINT_PLUS_SIZE);
    }

    AnnMatrix *weights = ann->getWeights();
    if(weights != nullptr){
      double *ptr = weights->matrix;

      int halfX = (COORDINATE_BOX_UPLIMIT_X / 2);
      int halfY = (COORDINATE_BOX_UPLIMIT_Y / 2);

      /* W [0, 1, 2] = [a, b, c]
       * We know the equation ax + by + c = 0
       * so we can calculate y for x,
       * y = -(ax + c) / b */
      for(int i = 0; i < weights->row; i++){
        double a = ptr[i * 3];
        double b = ptr[i * 3 + 1];
        double c = ptr[i * 3 + 2];
        if(b == 0){
          b = 0.00001;
        }

        // Left top corner
        int px1 = -halfX;
        int py1 = (a * (px1) + c * zoomVal) / b;

        // Right bottom corner
        int px2 = halfX;
        int py2 = (a * (px2) + c * zoomVal) / b;

        QPen pen(parent->colors[i], WEIGHT_LINES_WIDTH);
        painter.setPen(pen);
        // convert to coordinate box point and draw line
        painter.drawLine(px1 + halfX, py1 + halfY, px2 + halfX, py2 + halfY);
      }
    }
  }

  painter.restore();
}

/*---------------------------------------------------------------------------*/
void CoordinateBox::mousePressEvent(QMouseEvent *event){
  QPoint pos(event->pos().x() - (COORDINATE_BOX_UPLIMIT_X / 2), 
              (COORDINATE_BOX_UPLIMIT_Y / 2) - event->pos().y());

  if(parent->getListWidget()->currentItem() == nullptr){
    parent->error(parent, "No list element selected!",
        "Please select list element before click area!");
  } else{
    parent->getAnn()->addPoint(pos.x(), pos.y(), \
      parent->getListWidget()->currentRow());
    repaint();

    qDebug() << "AddPoint: Class-" << parent->getListWidget()->currentRow() \
      << ": (" <<pos.x() << ", " << pos.y() << ")";
  }
}
