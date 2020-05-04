/**
 * \file
 *        Artificial Neural Network
 *
 * \author
 *        Kadir Yanık <kdrynkk@gmail.com>
 */
#include "Ann.h"
#include "AnnPoints.h"
#include "AnnMatrix.h"

#include <iostream>
#include <math.h>
#include <QPen>
#include <QDebug>

/*---------------------------------------------------------------------------*/
#define EACH_TRAIN_CYCLE_UPLIMIT 1000000

#define PRINT_FREQ 1000
#define PAINT_FREQ 1000

#define BIAS    1
#define EPSILON (0.001)

#define LEARNING_RATE_PERCEPTRON 0.2
#define LEARNING_RATE_DELTA 0.7

/*---------------------------------------------------------------------------*/
static int counterHolder;

/*---------------------------------------------------------------------------*/
Ann::Ann(int outputLayerSize, bool deltaRule, bool normalizeEnabled,
         CoordinateBox *coordinateBox, AnnMatrix *W){
  this->K = outputLayerSize;
  this->I = 2; // Input size: contain x, y

  this->deltaRule = deltaRule;

  this->normalizeEnabled = normalizeEnabled;
  this->pointsNormilized = false;

  this->coordinateBox = coordinateBox;
  this->W = W;
  if(W == nullptr){
    weightsInitialized = false;
  } else{
    weightsInitialized = true;
  }

  pointList = new AnnPoints();
  normilizedPointList = nullptr;
  dExpect = nullptr;

  srand(time(nullptr));
}

/*---------------------------------------------------------------------------*/
Ann::~Ann(){
  storePointsAndReset();

  // and delete points
  if(pointList) delete pointList;
}

/*---------------------------------------------------------------------------*/
bool Ann::train(){
  if(!weightsInitialized){
    initializeWeights();
  }
  if(normalizeEnabled && !pointsNormilized){
    normalizePoints();
  }

  int cycleCounter = 0;
  bool isDone = false;
  double E = 1;

  double c = LEARNING_RATE_PERCEPTRON;
  if(deltaRule) c = LEARNING_RATE_DELTA;

  AnnPoint *p = pointList->getPoints();
  if(pointsNormilized) p = normilizedPointList->getPoints();
  while(true){
    p = p->next();
    if (p == nullptr){
      if(pointsNormilized){
        p = normilizedPointList->getPoints();
      } else{
        p = pointList->getPoints();
      }
      cycleCounter++;

      if((cycleCounter % PAINT_FREQ) == 0){
        // repainting weights
        coordinateBox->repaint();
      }

      if((cycleCounter % PRINT_FREQ) == 0){
        qDebug() << "Ann-train: error = " << E;
      }

      if(isDone || E < EPSILON || \
        (cycleCounter >= EACH_TRAIN_CYCLE_UPLIMIT)){
        coordinateBox->repaint();
        qDebug() << "Ann-train: error = " << E;
        isDone = true;
        break;
      }

      // if not done reset error and start over
      E = 0;
      isDone = true;
      continue;
    }

    AnnMatrix *y = new AnnMatrix(this->K + 1, 1);
    y->matrix[0] = p->x();
    y->matrix[1] = p->y();
    y->matrix[2] = BIAS;

    AnnMatrix *d = (*W) * y;
    double *dFound = d->matrix;
    for(int i = 0; i < this->K; i++){
      double fTnet;
      double dMinusO = dExpect[i][p->classId()] - fNet(dFound[i], &fTnet);

      if(dMinusO > EPSILON || dMinusO < -EPSILON){
        E += 0.5 * dMinusO * dMinusO;

        AnnMatrix *wRow = W->getRowVector(i);
        AnnMatrix *wRowTranspoz = wRow->transpoz();

        (*wRowTranspoz) += ((*y) * (c * dMinusO * fTnet));
        W->updateRow(i, wRowTranspoz);

        // reset isDone flag
        isDone = false;

        // clean up
        delete wRow; delete wRowTranspoz;
      }
    }

    // clean up
    delete d; delete y;
  }

  qDebug() << "Ann-train: (" << counterHolder << " + " << cycleCounter << \
    ") cycle!";
  counterHolder += cycleCounter;

  qDebug() << "Ann-train: weights:";
  for(int i = 0; i < this->K; i++){
    qDebug() << "Ann-train:  " << W->matrix[i * 3] << " " << \
      W->matrix[i * 3 + 1] << " " << W->matrix[i * 3 + 2];
  }

  // repaint for weights
  coordinateBox->repaint();

  if(isDone){
    return true;
  }
  return false;
}

/*---------------------------------------------------------------------------*/
void Ann::addPoint(double x, double y, int classId){
  pointList->addPoint(x, y, classId);
}

/*---------------------------------------------------------------------------*/
AnnPoints* Ann::getPointList(){
  if(pointsNormilized){
    return normilizedPointList;
  }
  return pointList;
}

/*---------------------------------------------------------------------------*/
AnnMatrix* Ann::getWeights(){
  return W;
}

/*---------------------------------------------------------------------------*/
void Ann::setDeltaRule(bool deltaRule){
  this->deltaRule = deltaRule;
}

/*---------------------------------------------------------------------------*/
void Ann::setNormalizeEnabled(bool normalizeEnabled){
  this->normalizeEnabled = normalizeEnabled;

  if(normilizedPointList != nullptr){
    delete normilizedPointList;

    normilizedPointList = nullptr;
    pointsNormilized = false;
  }
}

/*---------------------------------------------------------------------------*/
void Ann::storePointsAndReset(){
  if(W != nullptr){
    delete W;

    W = nullptr;
    weightsInitialized = false;
  }

  if(normilizedPointList != nullptr){
    delete normilizedPointList;

    normilizedPointList = nullptr;
    pointsNormilized = false;
  }

  if(dExpect != nullptr){
    // clean up memory
    for(int i = 0; i < this->K; i++){
      delete [] dExpect[i];
    }
    delete [] dExpect;
  
    dExpect = nullptr;
  }
}

/*---------------------------------------------------------------------------*/
void Ann::deleteLastPoint(){
  AnnPoint *p = pointList->getPoints();
  if(p->next() == nullptr){ // list is empty
    return;
  }

  // find last point
  while(p->next()->next() != nullptr){
    p = p->next();
  }

  delete p->next();
  p->setNext(nullptr);
}

/*---------------------------------------------------------------------------*/
/*----------------------------Private-Functions------------------------------*/
/*---------------------------------------------------------------------------*/
void Ann::initializeWeights(){
  W = new AnnMatrix(K, I + 1);

  // set random numbers weight matrixes
  for(int i = 0; i < W->row; i++){
    for (int j = 0; j < W->column; j++){
      W->matrix[i * W->column + j] = ((double)rand() / RAND_MAX);
    }
  }
  weightsInitialized = true;

  // alloc and fill dExpect
  this->dExpect = new int*[this->K];

  for(int i = 0; i < this->K; i++){
    this->dExpect[i] = new int[this->K];

    for(int j = 0; j < this->K; j++){
      if(i == j){
        this->dExpect[i][j] = 1;
      } else{
        this->dExpect[i][j] = -1;
      }
    }
  }
}

/*---------------------------------------------------------------------------*/
void Ann::normalizePoints(){
  if(normilizedPointList != nullptr){
    delete normilizedPointList;
  }
  normilizedPointList = new AnnPoints();

  double *totals = new double[I];
  double *standartDevs = new double[I];
  double *sumOfSquares = new double[I];
  double *variances = new double[I];

  int pointNumber = 0;

  AnnPoint* p = pointList->getPoints();
  while((p = p->next()) != nullptr){
    for(int i = 0; i < I; i++){
      totals[i] += p->data()[i];
      sumOfSquares[i] += (p->data()[i] * p->data()[i]);
    }

    pointNumber++;
  }

  for(int i = 0; i < I; i++){
    totals[i] /= pointNumber;
    variances[i] = (sumOfSquares[i] / pointNumber) - (totals[i] * totals[i]);
  }

  for(int i = 0; i < I; i++){
    standartDevs[i] = sqrt(variances[i]);
  }

  // Set points
  p = pointList->getPoints();
  while ((p = p->next()) != nullptr){
    double data[I];
    for(int i = 0; i < I; i++){
      data[i] = (p->data()[i] - totals[i]) / standartDevs[i];
    }

    normilizedPointList->addPoint(data[0], data[1], p->classId());
  }

  pointsNormilized = true;

  // clean up
  if(totals) delete [] totals;
  if(standartDevs) delete [] standartDevs;
  if(sumOfSquares) delete [] sumOfSquares;
  if(variances) delete [] variances;
}

/*---------------------------------------------------------------------------*/
double Ann::fNet(double net, double *fTnet){
  if(deltaRule){
    double temp = exp(-net) + 1;
    if (temp == 0){
      temp = 0.0000001;
    }
    double fNet = (2.0 / (temp) - 1.0);

    *fTnet = 0.5 * (1 - (fNet * fNet));
    return fNet;
  } else{
    *fTnet = 1;
    return (net >= 0 ? 1 : -1);
  }
}
