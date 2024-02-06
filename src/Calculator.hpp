// Copyright EsperaActiva

/**
 * @file Calculator.hpp 
 * @brief Class in charge of performing mathematical calculations
 * @author Team EsperaActiva
 * @date 11/2021
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

#include "Matrix.hpp"

class Calculator {
 private:
  /**
   * @brief Updates a cell in newMatrix to reflex the change in temperature
   *  this particular state of the simulation
   * 
   * @param prevMatrix Is the matrix in the previous state on the simulation
   * @param newMatrix A matrix with the updated state
   * @param row Specific row to modify
   * @param col Specific column to modify
   * @param time elapsed time between each matrix state, it is used in the formule.
   * @param alpha thermal diffusivity inherent to the plate
   * @param h plate dimensions
   */
  static void sumTemps(Matrix* prevMatrix, Matrix* newMatrix
    , size_t row, size_t col, double time, double alpha, double h);

 public:
  /**
   * @brief Updates the state of each cell in the previous state for this plate.
   * 
   * @param prevMatrix Is the matrix in the previous state in the simulation
   * @param newMatrix A matrix with the updated state of one particular cell
   * @param time increase in seconds between each matrix state, it is used in the formule.
   * @param alpha thermal diffusivity inherent to the plate
   * @param h plate dimensions
   * @param thread_count number of threads
   */
  static void calcTemperature(Matrix* prevMatrix, Matrix* newMatrix
    , double time, double alpha, double h, int& thread_count);

  /**
   * @brief Method that returns true if the matrix is stable
   * @param matrizActual Matrix with the updated temperatures
   * @param prevMatrix Is the matrix in the previous state in the simulation
   * @param epsilon Defines max change a cell can have to be considered stable
   * @return true if there wasnt a change bigger than epsilon in any of the cells between this state and the previous one
   * @return false if there was a change bigger than epsilon
   */
  static bool isStable(Matrix* matrizActual
    , Matrix* prevMatrix, double& epsilon);

  /**
   * @brief This method converts the elapse time to the human readable
   * format
   * 
   * @param elapsedTime 
   * @return std::string 
   */
  static std::string secondsToDate(double elapsedTime);

  /**
   * @brief Copies the numeric value allocated in the borders of prevMatrix into newMatrix
   * 
   * @param prevMatrix The matrix holding the previous plate-state
   * @param newMatrix The matrix in which new update values will be stores,
   *  will hold the next state for this plate
   */
  static void copyPlateEdges(Matrix* prevMatrix, Matrix* newMatrix);
};
#endif  // CALCULATOR_H
