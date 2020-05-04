/**
 * \file
 *        Simple linked list node.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#ifndef ANNPOINT_H
#define ANNPOINT_H

/*---------------------------------------------------------------------------*/
class AnnPoint
{
private:
  AnnPoint *nextPtr;
  double dataArr[2]; // contain x, y
  int classIdVar;
public:
  AnnPoint(double = 0, double = 0, int classId = 0);
  ~AnnPoint();
  
  AnnPoint* next();
  double x();
  double y();
  double* data();
  int classId();

  void setNext(AnnPoint *next);
  void setX(double x);
  void setY(double y);
};

#endif // ANNPOINT_H
