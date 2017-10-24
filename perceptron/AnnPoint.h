#pragma once
class AnnPoint
{
private:
	AnnPoint* next;
	int x;
	int y;
	int classId;
public:
	AnnPoint(int = 0, int = 0, int classId = 0);
	~AnnPoint();
	void setNext(AnnPoint* n);
	AnnPoint* getNext();
	int getX();
	int getY();
	int getClassId();
};

