#pragma once
#include "AnnPoint.h"

ref class AnnPoints
{
private:
	AnnPoint* points;
public:
	AnnPoints();
	~AnnPoints();
	AnnPoint* getPoints();
	void addPoint(double x, double y, int classId);
};

