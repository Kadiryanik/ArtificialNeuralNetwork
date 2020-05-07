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

    if(ann->isTrained()){
      int halfX = (COORDINATE_BOX_UPLIMIT_X / 2);
      int halfY = (COORDINATE_BOX_UPLIMIT_Y / 2);

      for(int i = -halfX; i < halfX; i += 3){
        for(int j = halfY; j > -halfY; j -= 3){
          int classId = ann->test(i, j);

          QPen pen(parent->colors[classId], 1);
          painter.setPen(pen);

          painter.drawLine(i + halfX, halfY - j, i + halfX + 1, halfY - j);
        }
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
