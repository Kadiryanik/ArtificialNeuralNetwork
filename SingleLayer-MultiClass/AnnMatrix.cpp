/**
 * \file
 *        ANN Matrix Lib.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#include "AnnMatrix.h"

/*---------------------------------------------------------------------------*/
AnnMatrix::AnnMatrix(){
  this->row = 0;
  this->column = 0;
  matrix = nullptr;
}

/*---------------------------------------------------------------------------*/
AnnMatrix::AnnMatrix(int row, int column){
  this->row = row;
  this->column = column;

  matrix = new double[row * column];
  for(int i = 0; i < row * column; i++){
    matrix[i] = 0;
  }
}

/*---------------------------------------------------------------------------*/
AnnMatrix::~AnnMatrix(){
  if(matrix) delete [] matrix;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::getColumnVector(int i){
  AnnMatrix *temp = new AnnMatrix(this->row, 1);

  for(int j = 0; j < this->row; j++){
    temp->matrix[j] = this->matrix[i + j * this->column];
  }
  return temp;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::getRowVector(int i){
  AnnMatrix *temp = new AnnMatrix(1, this->column);

  for(int j = 0; j < this->column; j++){
    temp->matrix[j] = this->matrix[i * this->column + j];
  }
  return temp;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::updateRow(int i, AnnMatrix *other){
  for(int j = 0; j < other->row; j++){
    this->matrix[i * this->column + j] = other->matrix[j];
  }
  return this;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::transpoz(){
  AnnMatrix* temp = new AnnMatrix(this->column, this->row);
  int k = 0;

  for(int i = 0; i < this->column; i++){
    for(int j = 0; j < this->row; j++){
      temp->matrix[k] = this->matrix[i + j * column];
      k++;
    }
  }

  return temp;
}

/*---------------------------------------------------------------------------*/
int AnnMatrix::maxSelector(){
  int max = this->matrix[0];
  int ret = 0;
  for(int i = 1; i < this->row * this->column; i++){
    if(max < this->matrix[i]){
      max = this->matrix[i];
      ret = i;
    }
  }
  return ret;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::operator+(const AnnMatrix *other){
  int bigRow;
  int bigColumn;

  if(this->row > other->row){
    bigRow = this->row;
  } else{
    bigRow = other->row;
  }

  if(this->column > other->column){
    bigColumn = this->column;
  } else{
    bigColumn = other->column;
  }

  AnnMatrix* temp = new AnnMatrix(bigRow, bigColumn);
  for(int i = 0; i < this->row; i++){
    for(int j = 0; j < this->column; j++){
      temp->matrix[i * bigColumn + j] = this->matrix[i * this->column + j];
    }
  }

  for(int i = 0; i < other->row; i++){
    for(int j = 0; j < other->column; j++){
      temp->matrix[i * bigColumn + j] += other->matrix[i * other->column + j];
    }
  }
  return temp;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::operator+=(const AnnMatrix *other){
  for(int i = 0; i < this->row; i++){
    for(int j = 0; j < this->column; j++){
      this->matrix[i * this->column + j] += other->matrix[i * other->column + j];
    }
  }
  return this;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::operator-(const AnnMatrix *other){
  int bigRow;
  int bigColumn;

  if(this->row > other->row){
    bigRow = this->row;
  } else{
    bigRow = other->row;
  }

  if(this->column > other->column){
    bigColumn = this->column;
  } else{
    bigColumn = other->column;
  }

  AnnMatrix *temp = new AnnMatrix(bigRow, bigColumn);
  for(int i = 0; i < this->row; i++){
    for(int j = 0; j < this->column; j++){
      temp->matrix[i * bigColumn + j] = this->matrix[i * this->column + j];
    }
  }

  for(int i = 0; i < other->row; i++){
    for(int j = 0; j < other->column; j++){
      temp->matrix[i * bigColumn + j] -= other->matrix[i * other->column + j];
    }
  }

  return temp;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::operator*(const AnnMatrix *other){
  AnnMatrix *temp = nullptr;
  if(this->row == other->row && this->column == other->column){
    temp = new AnnMatrix(this->row, this->column);

    for(int i = 0; i < this->row; i++){
      for(int j = 0; j < this->column; j++){
        temp->matrix[i * this->column + j] = this->matrix[i * this->column + j]
                * other->matrix[i * this->column + j];
      }
    }
    return temp;
  }

  temp = new AnnMatrix(this->row, other->column);
  for(int i = 0; i < this->row; i++){
    for(int t = 0; t < other->column; t++){
      for(int j = 0; j < this->column; j++){
        temp->matrix[i * other->column + t] += this->matrix[i * this->column + j]
                * other->matrix[t + j * other->column];
      }
    }
  }

  return temp;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::operator*(double k){
  for(int i = 0; i < this->row * this->column; i++){
    this->matrix[i] *= k;
  }

  return this;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* AnnMatrix::operator=(const AnnMatrix *other){
  this->row = other->row;
  this->column = other->column;

  matrix = new double[this->row * this->column];

  for(int i = 0; i < other->column * other->row; i++){
    this->matrix[i] = other->matrix[i];
  }
  return this;
}
