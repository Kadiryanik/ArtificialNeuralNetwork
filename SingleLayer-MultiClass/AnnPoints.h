/**
 * \file
 *        Simple linked list.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#ifndef ANNPOINTS_H
#define ANNPOINTS_H

#include "AnnPoint.h"

/*---------------------------------------------------------------------------*/
class AnnPoints
{
private:
  AnnPoint* points;
public:
  AnnPoints();
  ~AnnPoints();
  
  void addPoint(double x, double y, int classId);
  AnnPoint* getPoints();
};

#endif // ANNPOINTS_H
