/**
 * \file
 *        ANN Matrix Lib.
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#ifndef ANNMATRIX_H
#define ANNMATRIX_H

#include <iostream>

/*---------------------------------------------------------------------------*/
class AnnMatrix
{
public:
  int row;
  int column;
  double *matrix;

  AnnMatrix();
  AnnMatrix(int row, int column);
  ~AnnMatrix();

  int maxSelector();
  AnnMatrix* getColumnVector(int i);
  AnnMatrix* getRowVector(int i);
  AnnMatrix* updateRow(int i, AnnMatrix *other);
  AnnMatrix* transpoz();
  
  AnnMatrix* operator+(const AnnMatrix *other);
  AnnMatrix* operator+=(const AnnMatrix *other);
  AnnMatrix* operator-(const AnnMatrix *other);
  AnnMatrix* operator*(const AnnMatrix *other);
  AnnMatrix* operator*(double k);
  AnnMatrix* operator=(const AnnMatrix *other);
};

#endif // ANNMATRIX_H
