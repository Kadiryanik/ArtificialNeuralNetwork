#include "AnnPoint.h"

AnnPoint::AnnPoint(double x, double y, int classId)
{
	this->next = nullptr;
	this->x = x;
	this->y = y;
	this->classId = classId;
}

AnnPoint::~AnnPoint()
{
	if (next != nullptr){
		next->~AnnPoint();
	}
}

void AnnPoint::setNext(AnnPoint* n){
	this->next = n;
}

AnnPoint* AnnPoint::getNext(){
	return this->next;
}

double AnnPoint::getX(){
	return x;
}

double AnnPoint::getY(){
	return y;
}

void AnnPoint::setX(double i){
	this->x = i;
}

void AnnPoint::setY(double i){
	this->y = i;
}

int AnnPoint::getClassId(){
	return classId;
}