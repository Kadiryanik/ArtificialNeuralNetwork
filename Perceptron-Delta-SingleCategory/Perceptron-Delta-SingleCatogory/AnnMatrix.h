#pragma once
ref class AnnMatrix
{
private:
	double *matrix;
	int row;
	int column;
public:
	AnnMatrix();
	AnnMatrix(int row, int column);
	~AnnMatrix();
	double* getMatrix();
	int getRow();
	int getColumn();
	AnnMatrix^ getColumnVector(int i);
	AnnMatrix^ transpoz();

	AnnMatrix^ operator+(const AnnMatrix^ other);
	AnnMatrix^ operator+=(const AnnMatrix^ other);
	AnnMatrix^ operator-(const AnnMatrix^ other);
	AnnMatrix^ operator*(const AnnMatrix^ other);
	AnnMatrix^ operator*(double k);
	AnnMatrix% operator=(const AnnMatrix% other);
};

