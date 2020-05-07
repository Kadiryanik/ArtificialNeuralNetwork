/**
 * \file
 *        Simple linked list node.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#include "AnnPoint.h"

/*---------------------------------------------------------------------------*/
AnnPoint::AnnPoint(double x, double y, int classId){
  this->nextPtr = nullptr;
  this->dataArr[0] = x;
  this->dataArr[1] = y;

  this->classIdVar = classId;
}

/*---------------------------------------------------------------------------*/
AnnPoint::~AnnPoint(){
  if (nextPtr != nullptr){
    nextPtr->~AnnPoint();
  }
}

/*---------------------------------------------------------------------------*/
AnnPoint* AnnPoint::next(){
  return this->nextPtr;
}

/*---------------------------------------------------------------------------*/
double AnnPoint::x(){
  return this->dataArr[0];
}

/*---------------------------------------------------------------------------*/
double AnnPoint::y(){
  return this->dataArr[1];
}

/*---------------------------------------------------------------------------*/
double* AnnPoint::data(){
  return this->dataArr;
}

/*---------------------------------------------------------------------------*/
int AnnPoint::classId(){
  return classIdVar;
}

/*---------------------------------------------------------------------------*/
void AnnPoint::setNext(AnnPoint *next){
  this->nextPtr = next;
}

/*---------------------------------------------------------------------------*/
void AnnPoint::setX(double i){
  this->dataArr[0] = i;
}

/*---------------------------------------------------------------------------*/
void AnnPoint::setY(double i){
  this->dataArr[1] = i;
}
