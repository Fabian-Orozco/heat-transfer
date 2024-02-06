// Copyright EsperaActiva

/**
 * @file Simulation.hpp 
 * @brief Class in charge of simulating the heat transfer in the states of the plates
 * @author Team EsperaActiva
 * @date 11/2021
 */

#ifndef SIMULATION_
#define SIMULATION_
#include <time.h>
#include "Matrix.hpp"

class Simulation {
 private:
  Matrix* prevMatrix; /**< represents the previous state of a matrix**/
  Matrix* currentMatrix; /**< represents the current state of a matrix**/

 public:
  /**
   * @brief Class default constructor
   */
  Simulation();

  /**
   * @brief Class destructor
   */
  ~Simulation();

  /**
   * @brief Simulates the plate heat tranfer
   * 
   * @details sets Matrixes, calls the calculation methods, checks if
   * the matrixes are stable to stop this job; in the case the plate have not
   * encounter a stable status, keeps running simulation.
   * Updates the matrixes cell values accordingly. 
   * 
   * @param time elapsed time between each matrix state, it is used in the formule.
   * @param alpha thermal diffusivity inherent to the plate
   * @param h plate dimensions
   * @param epsilon defines max change a cell can have to be considered stable
   * @param thread_count number of threads
   * @param currentK number k representing the current state
   * @return double representing elapsed time
   */
  double start(double time, double alpha, double h, double epsilon,
    int& thread_count, int& currentK);

  /**
   * @brief method that shows the previous state of the matrix
   * 
   * @return pointer to previous state of a matrix
   */
  Matrix* getPrevMatrix();

  /**
   * @brief method that shows the current state of the matrix
   * 
   * @return Matrix* pointer to current state of a matrix
   */
  Matrix* getCurrentMatrix();

  /**
   * @brief Sets the prev matrix for the simulation and creates the current one
   * 
   * @param matrix 2D array to be initialized
   */
  void setMatrix(Matrix* matrix);
};

#endif  //  SIMULATION_
