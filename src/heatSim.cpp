// Copyright EsperaActiva

/**
 * @file heatSim.cpp 
 * @brief Program main
 * @author Team EsperaActiva
 * @date 11/2021
 */
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "SimulationManager.hpp"

/**
 * @brief program main, starts the simulation
 * 
 * @param argc represent the number of arguments
 * @param argv represent the array with the arguments
 */
int main(int argc, char* argv[]) {
  SimulationManager manager;

  manager.start(argc, argv);

  return EXIT_SUCCESS;
}
