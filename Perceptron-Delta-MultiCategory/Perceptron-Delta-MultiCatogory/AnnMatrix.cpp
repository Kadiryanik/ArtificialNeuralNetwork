#include "AnnMatrix.h"

AnnMatrix::AnnMatrix()
{
	this->row = 0;
	this->column = 0;
	matrix = nullptr;
}
AnnMatrix::AnnMatrix(int row, int column)
{
	this->row = row;
	this->column = column;

	matrix = new double[row * column];
	int i;
	for (i = 0; i < row * column; i++){
		matrix[i] = 0;
	}
}
AnnMatrix::~AnnMatrix(){
	delete[] matrix;
}

double* AnnMatrix::getMatrix(){
	return matrix;
}
int AnnMatrix::getRow(){
	return this->row;
}
int AnnMatrix::getColumn(){
	return this->column;
}

AnnMatrix^ AnnMatrix::getColumnVector(int i){
	AnnMatrix^ temp = gcnew AnnMatrix(this->row, 1);
	int j;

	for (j = 0; j < this->row; j++){
		temp->matrix[j] = this->matrix[i + j * this->column];
	}
	return temp;
}

AnnMatrix^ AnnMatrix::getRowVector(int i){
	AnnMatrix^ temp = gcnew AnnMatrix(1, this->column);
	int j;

	for (j = 0; j < this->column; j++){
		temp->matrix[j] = this->matrix[i * this->column + j];
	}
	return temp;
}

AnnMatrix^ AnnMatrix::updateRow(int i, AnnMatrix^ other){
	int j;

	for (j = 0; j < other->row; j++){
		this->matrix[i * this->column + j] = other->matrix[j];
	}
	return this;
}

AnnMatrix^ AnnMatrix::transpoz(){
	AnnMatrix^ temp = gcnew AnnMatrix(this->column, this->row);
	int i, j, k = 0;

	for (i = 0; i < this->column; i++){
		for (j = 0; j < this->row; j++){
			temp->matrix[k] = this->matrix[i + j * column];
			k++;
		}
	}

	return temp;
}

AnnMatrix^ AnnMatrix::operator+(const AnnMatrix^ other){
	int i, j;
	int size = this->row * this->column;
	
	int bigRow;
	int bigColumn;

	if (this->row > other->row){
		bigRow = this->row;
	}
	else{
		bigRow = other->row;
	}
	if (this->column > other->column){
		bigColumn = this->column;
	}
	else{
		bigColumn = other->column;
	}

	AnnMatrix^ temp = gcnew AnnMatrix(bigRow, bigColumn);
	for (i = 0; i < this->row; i++){
		for (j = 0; j < this->column; j++){
			temp->matrix[i * bigColumn + j] = this->matrix[i * this->column + j];
		}
	}

	for (i = 0; i < other->row; i++){
		for (j = 0; j < other->column; j++){
			temp->matrix[i * bigColumn + j] += other->matrix[i * other->column + j];
		}
	}
	return temp;
}

AnnMatrix^ AnnMatrix::operator+=(const AnnMatrix^ other){
	int i, j;
	for (i = 0; i < this->row; i++){
		for (j = 0; j < this->column; j++){
			this->matrix[i * this->column + j] += other->matrix[i * other->column + j];
		}
	}
	return this;
}

AnnMatrix^ AnnMatrix::operator-(const AnnMatrix^ other){
	int i, j;
	int size = this->row * this->column;
	int bigRow;
	int bigColumn;

	if (this->row > other->row){
		bigRow = this->row;
	}
	else{
		bigRow = other->row;
	}
	if (this->column > other->column){
		bigColumn = this->column;
	}
	else{
		bigColumn = other->column;
	}

	AnnMatrix^ temp = gcnew AnnMatrix(bigRow, bigColumn);
	for (i = 0; i < this->row; i++){
		for (j = 0; j < this->column; j++){
			temp->matrix[i * bigColumn + j] = this->matrix[i * this->column + j];
		}
	}

	for (i = 0; i < other->row; i++){
		for (j = 0; j < other->column; j++){
			temp->matrix[i * bigColumn + j] -= other->matrix[i * other->column + j];
		}
	}

	return temp;
}

AnnMatrix^ AnnMatrix::operator*(const AnnMatrix^ other){
	int i, j, t;
	AnnMatrix^ temp = gcnew AnnMatrix(this->row, other->column);

	for (i = 0; i < this->row; i++){
		for (t = 0; t < other->column; t++){
			for (j = 0; j < this->column; j++){
				temp->matrix[i * other->column + t] += this->matrix[i * this->column + j] * other->matrix[t + j * other->column];
			}
		}
	}

	return temp;
}

AnnMatrix^ AnnMatrix::operator*(double k){
	int i;

	for (i = 0; i < this->row * this->column; i++){
		this->matrix[i] *= k;
	}

	return this;
}

AnnMatrix% AnnMatrix::operator=(const AnnMatrix% other){
	int i;
	this->row = other.row;
	this->column = other.column;
	
	matrix = new double[this->row * this->column];

	for (i = 0; i < other.column * other.row; i++){
		this->matrix[i] = other.matrix[i];
	}
	return *this;
}
