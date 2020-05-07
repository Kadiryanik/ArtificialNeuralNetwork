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

#define PRINT_FREQ 100

#define BIAS    1
#define EPSILON (0.0001)

/*---------------------------------------------------------------------------*/
static int counterHolder;

/*---------------------------------------------------------------------------*/
Ann::Ann(int outputLayerSize, CoordinateBox *coordinateBox, AnnMatrix *W, \
         AnnMatrix *V){
  this->K = outputLayerSize;
  this->J = this->K + (this->K / 2); // TODO: set with user input
  this->I = 2; // Input size: contain x, y

  this->pointsNormilized = false;

  this->coordinateBox = coordinateBox;
  this->W = W;
  this->V = V;
  if(W == nullptr || V == nullptr){
    weightsInitialized = false;
  } else{
    weightsInitialized = true;
  }

  pointList = new AnnPoints();
  normilizedPointList = nullptr;
  totals = nullptr;
  standartDevs = nullptr;

  trained = false;
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
  if(!pointsNormilized){
    normalizePoints();
  }

  // repaint points
  coordinateBox->repaint();

  int cycleCounter = 0;
  bool isDone = false;
  double E = 1;

  AnnPoint *p = normilizedPointList->getPoints();
  while(true){
    p = p->next();
    if(p == nullptr){
      p = normilizedPointList->getPoints();

      cycleCounter++;
      if((cycleCounter % PRINT_FREQ) == 0){
        qDebug() << "Ann-train: error = " << E;
      }
      if(E < EPSILON){
        isDone = true;
        this->trained = true;
        break;
      } else if(cycleCounter >= EACH_TRAIN_CYCLE_UPLIMIT){
        isDone = false;
        break;
      }

      // if isn't done yet reset error and start over
      E = 0;
      continue;
    }

    AnnMatrix *z = new AnnMatrix(I + 1, 1);
    z->matrix[0] = p->x();
    z->matrix[1] = p->y();
    z->matrix[2] = BIAS;

    // J x 1
    AnnMatrix *tempY = (*V) * z;
    this->fNet(tempY);

    // Add bias to y: (J + 1) x 1
    AnnMatrix *y = new AnnMatrix(tempY->row + 1, tempY->column);
    
    for(int i = 0; i < tempY->row; i++){
      y->matrix[i] = tempY->matrix[i];
    }
    y->matrix[tempY->row] = BIAS;

    // W: K x (J + 1), y: (J + 1) x 1
    AnnMatrix *o = (*W) * y; // K x 1
    this->fNet(o);

    AnnMatrix *d = new AnnMatrix(K, 1);
    for(int i = 0; i < K; i++){
      if(p->classId() == i){
        d->matrix[i] = 1;
      } else{
        d->matrix[i] = -1;
      }
    }
    // K x 1
    AnnMatrix *dMinusO = (*d) - o;

    for(int i = 0; i < K; i++){
      E += 0.5 * (dMinusO->matrix[i] * dMinusO->matrix[i]);
    }
    // K x 1
    AnnMatrix *fTnetK = new AnnMatrix(K, 1);
    for (int i = 0; i < K; i++){
      fTnetK->matrix[i] = 0.5 * (1 - (o->matrix[i] * o->matrix[i]));
    }

    // K x 1
    AnnMatrix *deltaO = (*dMinusO) * fTnetK;

    double _m = 1; //mü

    // K x 1 .. 1 x J+1
    AnnMatrix *yTranspoz = y->transpoz();
    
    // W update
    AnnMatrix *productTemp = ((*deltaO) * yTranspoz);
    (*W) += ((*productTemp) * _m);
    
    delete productTemp; delete yTranspoz;

    // J x 1
    AnnMatrix *fTnetJ = new AnnMatrix(J, 1);

    for(int i = 0; i < J; i++){
      fTnetJ->matrix[i] = 0.5 * (1 - (tempY->matrix[i] * tempY->matrix[i]));
    }

    // J x 1
    AnnMatrix *deltaY = new AnnMatrix(J, 1);

    for(int j = 0; j < J; j++){
      double sum = 0;
      for(int k = 0; k < K; k++){
        sum += deltaO->matrix[k] * W->matrix[k * W->column + j];
      }
      deltaY->matrix[j] = fTnetJ->matrix[j] * sum;
    }

    AnnMatrix *zTranspoz = z->transpoz();

    // V update
    productTemp = ((*deltaY) * zTranspoz);
    (*V) += ((*productTemp) * _m);

    // clean up
    delete productTemp; delete zTranspoz; delete z; delete tempY;
    delete y; delete o; delete d; delete dMinusO; delete deltaO;
    delete deltaY; delete fTnetJ; delete fTnetK;
  }

  qDebug() << "Ann-train: (" << counterHolder << " + " << cycleCounter << \
    ") cycle!";
  counterHolder += cycleCounter;

  return isDone;
}

/*---------------------------------------------------------------------------*/
int Ann::test(int pointX, int pointY){
  AnnMatrix *x = new AnnMatrix(this->I + 1, 1);
  x->matrix[0] = (pointX - totals[0]) / standartDevs[0];
  x->matrix[1] = (pointY - totals[1]) / standartDevs[1];
  x->matrix[2] = BIAS;

  AnnMatrix *tempY = ((*V) * x);
  this->fNet(tempY);

  AnnMatrix *y = new AnnMatrix(tempY->row + 1, tempY->column);
  for(int i = 0; i < tempY->row; i++){
    y->matrix[i] = tempY->matrix[i];
  }
  y->matrix[tempY->row] = BIAS;

  AnnMatrix *o = ((*W) * y);
  this->fNet(o);

  return o->maxSelector();
}

/*---------------------------------------------------------------------------*/
void Ann::addPoint(double x, double y, int classId){
  pointList->addPoint(x, y, classId);
}

/*---------------------------------------------------------------------------*/
AnnPoints* Ann::getPointList(){
  if(pointsNormilized && !trained){
    return normilizedPointList;
  }
  return pointList;
}

/*---------------------------------------------------------------------------*/
void Ann::storePointsAndReset(){
  if(W != nullptr){
    delete W;

    W = nullptr;
    weightsInitialized = false;
  }
  if(V != nullptr){
    delete V;

    V = nullptr;
    weightsInitialized = false;
  }

  if(normilizedPointList != nullptr){
    delete normilizedPointList;

    normilizedPointList = nullptr;
    pointsNormilized = false;
  }

  if(totals != nullptr){
    delete [] totals;
    totals = nullptr;
  }
  if(standartDevs != nullptr){
    delete [] standartDevs;
    standartDevs = nullptr;
  }

  trained = false;
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
bool Ann::isTrained(){
  return this->trained;
}

/*---------------------------------------------------------------------------*/
/*----------------------------Private-Functions------------------------------*/
/*---------------------------------------------------------------------------*/
void Ann::initializeWeights(){
  W = new AnnMatrix(K, J + 1);
  V = new AnnMatrix(J, I + 1);

  // set random numbers weight matrixes
  for(int i = 0; i < W->row; i++){
    for (int j = 0; j < W->column; j++){
      W->matrix[i * W->column + j] = ((double)rand() / RAND_MAX);
    }
  }  
  for(int i = 0; i < V->row; i++){
    for (int j = 0; j < V->column; j++){
      V->matrix[i * V->column + j] = ((double)rand() / RAND_MAX);
    }
  }

  weightsInitialized = true;
}

/*---------------------------------------------------------------------------*/
void Ann::normalizePoints(){
  if(normilizedPointList != nullptr){
    delete normilizedPointList;
  }
  normilizedPointList = new AnnPoints();

  if(totals != nullptr) delete [] totals;
  if(standartDevs != nullptr) delete [] standartDevs;

  totals = new double[I];
  standartDevs = new double[I];

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
  if(sumOfSquares) delete [] sumOfSquares;
  if(variances) delete [] variances;
}

/*---------------------------------------------------------------------------*/
void Ann::fNet(AnnMatrix *annMatrix){
  for(int i = 0; i < annMatrix->row; i++){
    for(int j = 0; j < annMatrix->column; j++){
      annMatrix->matrix[i * annMatrix->column + j] = (2 / (1 + exp(-annMatrix->matrix[i * annMatrix->column + j]))) - 1;
    }
  }
}
