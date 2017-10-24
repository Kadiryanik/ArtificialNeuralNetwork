#include "AnnPoint.h"

AnnPoint::AnnPoint(int x, int y, int classId)
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

int AnnPoint::getX(){
	return x;
}

int AnnPoint::getY(){
	return y;
}

int AnnPoint::getClassId(){
	return classId;
}