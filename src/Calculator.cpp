// Copyright EsperaActiva
#include <omp.h>
#include <cmath>  // abs
#include <string>

#include "Matrix.hpp"
#include "Calculator.hpp"

void Calculator::sumTemps(Matrix* prevMatrix, Matrix* newMatrix
  , size_t row, size_t col, double time, double alpha, double h) {
  double valorActual = (*prevMatrix)[row][col];
  double receivedEnergy = (*prevMatrix)[row-1][col] + (*prevMatrix)[row][col+1]
                      + (*prevMatrix)[row+1][col] + (*prevMatrix)[row][col-1];
  double energyDistr = 4.0 * valorActual;
  double addedEnergy = ((time * alpha) / (h*h))*(receivedEnergy - energyDistr);

  (*newMatrix)[row][col] = valorActual + addedEnergy;
}

void Calculator::copyPlateEdges(Matrix* prevMatrix, Matrix* newMatrix) {
  size_t maxRow = prevMatrix->getRows()-1;
  size_t maxCol = prevMatrix->getColumns()-1;
  for (size_t i = 0; i < prevMatrix->getColumns(); ++i) {
    (*newMatrix)[0][i] = (*prevMatrix)[0][i];
    (*newMatrix)[maxRow][i] = (*prevMatrix)[maxRow][i];
  }

  for (size_t j = 1; j < prevMatrix->getRows()-1; ++j) {
    (*newMatrix)[j][0] = (*prevMatrix)[j][0];
    (*newMatrix)[j][maxCol] = (*prevMatrix)[j][maxCol];
  }
}

void Calculator::calcTemperature(Matrix* prevMatrix, Matrix* newMatrix
  , double time, double alpha, double h, int& thread_count) {
  size_t rows = prevMatrix->getRows()-1;
  size_t columns = prevMatrix->getColumns()-1;
  // Divide the work among the threads at the best possible way.
  #pragma omp parallel for collapse(2) num_threads(thread_count) default(none) \
    shared(prevMatrix, newMatrix, time, alpha, h, rows, columns) \
    schedule(static, 1)
    for (size_t currentRow = 1; currentRow < rows ;
    ++currentRow) {
      for (size_t currentColumn = 1; currentColumn < columns;
        ++currentColumn) {
        sumTemps(prevMatrix, newMatrix, currentRow, currentColumn
          , time, alpha, h);
      }
    }
}

bool Calculator::isStable(Matrix* matrizActual
  , Matrix* prevMatrix, double& epsilon) {
  size_t rows = matrizActual->getRows()-1;
  size_t columns = matrizActual->getColumns()-1;
  double cambio = 0.0;
  for (size_t currentRow = 1; currentRow < rows;
  ++currentRow) {
    for (size_t currentColumn = 1; currentColumn < columns;
     ++currentColumn) {
      cambio = std::abs((*matrizActual)[currentRow][currentColumn]
        - (*prevMatrix)[currentRow][currentColumn]);

      if (cambio > epsilon) {
        return false;  // the plate temperatures are not stable yet
      }
    }
  }
  return true;
}

std::string Calculator::secondsToDate(double elapsedTime) {
  int seconds = elapsedTime;
  int minutes = seconds/60;
  int hours = minutes/60;
  int days = 0;
  int months = 0;
  int years = 0;

  seconds = elapsedTime;
  minutes = static_cast<int>(seconds/60);
  hours = static_cast<int>(minutes/60);
  days = static_cast<int>(hours/24);
  months = static_cast<int>(days/30);
  years = static_cast<int>(months/12);

  std::string timestamp;
  int mod = 0;

  if (years < 10) {
    timestamp += "000" + std::to_string(years)+"/";
  } else if (years < 100) {
    timestamp += "00" + std::to_string(years)+"/";
  } else if (years < 1000) {
    timestamp += "0" + std::to_string(years)+"/";
  } else if (!years) {
    timestamp += "0000/";
  } else {
    timestamp += std::to_string(years)+":";
  }

  mod = months%12;
  if (!mod) {
    timestamp += "00/";
  } else if (mod < 10) {
    timestamp += "0" + std::to_string(mod)+"/";
  } else {
    timestamp += std::to_string(mod)+"/";
  }

  mod = days%30;
  if (!mod) {
    timestamp += "00  ";
  } else if (mod < 10) {
    timestamp += "0" + std::to_string(mod)+ "  ";
  } else {
    timestamp += std::to_string(mod)+ "  ";
  }

  mod = hours%24;
  if (!mod) {
    timestamp += "00:";
  } else if (mod < 10) {
    timestamp += "0" + std::to_string(mod)+":";
  } else {
    timestamp += std::to_string(mod)+":";
  }
  mod = minutes%60;
  if (!mod) {
    timestamp += "00:";
  } else if (mod < 10) {
    timestamp += "0" + std::to_string(mod)+":";
  } else {
    timestamp += std::to_string(mod)+":";
  }
  mod = seconds%60;
  if (!mod) {
    timestamp += "00";
  } else if (mod < 10) {
    timestamp += "0" + std::to_string(mod);
  } else {
    timestamp += std::to_string(mod);
  }
  return timestamp;
}
