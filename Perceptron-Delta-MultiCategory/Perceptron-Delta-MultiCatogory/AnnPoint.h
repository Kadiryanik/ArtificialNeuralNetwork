#pragma once
class AnnPoint
{
private:
	AnnPoint* next;
	double x;
	double y;
	int classId;
public:
	AnnPoint(double = 0, double = 0, int classId = 0);
	~AnnPoint();
	void setNext(AnnPoint* n);
	AnnPoint* getNext();
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	int getClassId();
};

