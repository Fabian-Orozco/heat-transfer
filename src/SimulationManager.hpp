// Copyright EsperaActiva

/**
 * @file SimulationManager.hpp 
 * @brief Module of varied utilities.
 * @author Team EsperaActiva
 * @date 11/2021
 */

#ifndef SimulationManager_H
#define SimulationManager_H

#include <vector>
#include <string>

#include "BINRead.hpp"
#include "Matrix.hpp"
#include "Simulation.hpp"
#include "Reader.hpp"

class SimulationManager {
 public:
  /**
   * @brief Receives the arguments and is responsible for the execution of
   * the simulation
   * @details Reads the files, creates the struct of plates, which contains
   * all the information about the plates, also gets the matrix from the file
   * and does the simulation
   * 
   * @param argc argument count
   * @param argv array of chars holding the arguments received when executed
   */
  void start(int argc, char* argv[]);
};

#endif  // SimulationManager_H
