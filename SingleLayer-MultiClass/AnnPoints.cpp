/**
 * \file
 *        Simple linked list.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#include "AnnPoints.h"

#include <iostream>

/*---------------------------------------------------------------------------*/
AnnPoints::AnnPoints(){
  this->points = new AnnPoint();
}

/*---------------------------------------------------------------------------*/
AnnPoints::~AnnPoints(){
  if (this->points != nullptr){
    delete this->points;
  }
}

/*---------------------------------------------------------------------------*/
void AnnPoints::addPoint(double x, double y, int classId){
  AnnPoint *p = points;
  while (p->next() != nullptr){
    p = p->next();
  }
  p->setNext(new AnnPoint(x, y, classId));
}

/*---------------------------------------------------------------------------*/
AnnPoint* AnnPoints::getPoints(){
  return points;
}
