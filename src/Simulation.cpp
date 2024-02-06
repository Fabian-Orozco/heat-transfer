// Copyright EsperaActiva

#include <algorithm>
#include <iostream>
#include <utility>

#include "Simulation.hpp"
#include "Calculator.hpp"

using std::swap;

Simulation::Simulation() {
  this->prevMatrix = nullptr;
  this->currentMatrix = nullptr;
}
Simulation::~Simulation() {
}
double Simulation::start(double time, double alpha, double h, double epsilon,
  int& thread_count, int& currentK) {
  double elapsedTime = 0;
  currentK = 0;

  while (!Calculator::isStable(this->prevMatrix, this->currentMatrix,
    epsilon)) {
    Calculator::calcTemperature(this->prevMatrix, this->currentMatrix, time,
      alpha, h, thread_count);
    std::swap(prevMatrix, currentMatrix);
    ++currentK;
  }

  elapsedTime = currentK*time;
  return elapsedTime;
}

Matrix* Simulation::getPrevMatrix() {
  return this->prevMatrix;
}
Matrix* Simulation::getCurrentMatrix() {
  return this->currentMatrix;
}

void Simulation::setMatrix(Matrix* matrix) {
  this->prevMatrix = matrix;
  this->currentMatrix = new Matrix(prevMatrix->getRows(),
    prevMatrix->getColumns());
  Calculator::copyPlateEdges(this->prevMatrix, this->currentMatrix);
}
