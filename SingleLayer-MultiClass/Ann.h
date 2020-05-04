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
  Ann(int outputLayerSize = 4, bool deltaRule = false, \
    bool normalizeEnabled = true, CoordinateBox *coordinateBox = nullptr, \
    AnnMatrix *W = nullptr);
  ~Ann();

  bool train();
  void addPoint(double x, double y, int classId);
  AnnPoints* getPointList();
  AnnMatrix* getWeights();
  void setDeltaRule(bool deltaRule);
  void setNormalizeEnabled(bool normalizeEnabled);
  void storePointsAndReset();
  void deleteLastPoint();
private:
  CoordinateBox *coordinateBox;
  AnnPoints *pointList;
  AnnPoints *normilizedPointList;
  AnnMatrix *W; // weights
  int** dExpect;

  int K; // output layer size
  int I; // input layer size

  bool deltaRule;
  bool normalizeEnabled;
  bool pointsNormilized;
  bool weightsInitialized;

  void initializeWeights();
  void normalizePoints();
  double fNet(double net, double *fTnet);
};

#endif // ANN_H
