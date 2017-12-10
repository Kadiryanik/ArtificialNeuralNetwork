#pragma once
ref class AnnMatrix
{
private:
	int row;
	int column;
public:
	double *matrix;

	AnnMatrix();
	AnnMatrix(int row, int column);
	~AnnMatrix();
	double* getMatrix();
	int getRow();
	int getColumn();
	AnnMatrix^ getColumnVector(int i);
	AnnMatrix^ getRowVector(int i);
	AnnMatrix^ updateRow(int i, AnnMatrix^ other);
	AnnMatrix^ transpoz();
	AnnMatrix^ fnet(int f);
	int maxSelector();

	AnnMatrix^ operator+(const AnnMatrix^ other);
	AnnMatrix^ operator+=(const AnnMatrix^ other);
	AnnMatrix^ operator-(const AnnMatrix^ other);
	AnnMatrix^ operator*(const AnnMatrix^ other);
	AnnMatrix^ operator*(double k);
	AnnMatrix% operator=(const AnnMatrix% other);
};

