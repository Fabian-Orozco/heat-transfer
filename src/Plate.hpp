// Copyright EsperaActiva

/**
 * @file Plate.hpp 
 * @brief Struct representing plates and their characteristics
 * @author Team EsperaActiva
 * @date 11/2021
 */

#ifndef PLATE_H
#define PLATE_H

#include <string>
#include <cstring>
#include "Matrix.hpp"

typedef struct Plate {
  std::string platePath;  ///< path of the plate
  std::string name;  ///< name of the plate
  std::string plateNumber;  ///< number of current plate
  double time;  ///< elapsed time between each matrix state
  double thermal_diffusivity;  ///< indicates at what rate the material manages
  ///< to transmit energy from a hot spot to a cold one through it
  double elapsedTime;  ///< how long it took for the simulation to end
  double dimensions;  ///< plate dimensions
  double breakeven;  ///< thermal equilibrium point that the plates must reach
  int kValue;  ///< how many cycles it took for the simulation to end
  Matrix* matrix;  ///< matrix representing the heat areas of the plate
} Plate_t;

#endif  // PLATE_H
