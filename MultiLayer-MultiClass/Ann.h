/**
 * \file
 *        Artificial Neural Network
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#ifndef ANN_H
#define ANN_H

#include "CoordinateBox.h"
#include "AnnPoints.h"
#include "AnnMatrix.h"

#include <QString>

/*---------------------------------------------------------------------------*/
class Ann
{
public:
  Ann(int outputLayerSize = 4, CoordinateBox *coordinateBox = nullptr, \
    AnnMatrix *W = nullptr, AnnMatrix *V = nullptr);
  ~Ann();

  bool train();
  int test(int pointX, int pointY);
  void addPoint(double x, double y, int classId);
  AnnPoints* getPointList();
  void storePointsAndReset();
  void deleteLastPoint();
  bool isTrained();
private:
  CoordinateBox *coordinateBox;
  AnnPoints *pointList;
  AnnPoints *normilizedPointList;
  AnnMatrix *W; // weights
  AnnMatrix *V; // weights
  double *totals;
  double *standartDevs;

  int K; // output layer size
  int J; // hidden layer size
  int I; // input layer size

  bool trained;
  bool pointsNormilized;
  bool weightsInitialized;

  void initializeWeights();
  void normalizePoints();
  void fNet(AnnMatrix *annMatrix);
};

#endif // ANN_H
