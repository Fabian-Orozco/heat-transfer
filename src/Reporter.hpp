// Copyright EsperaActiva

/**
 * @file Reporter.hpp 
 * @brief Class in charge of reporting the results of the calculations on the plates
 * @author Team EsperaActiva
 * @date 11/2021
 */

#ifndef REPORTER_
#define REPORTER_

#include <string>
#include <vector>

#include "Plate.hpp"
#include "Matrix.hpp"

class Reporter {
 public:
  /**
   * @brief This method reports back to the tsv file where it creates a .tsv
   * file with the name of the plate, the time to get to the next state, alpha
   * h and epsilon. It also adds the K states it went through and the elapsed
   * time.
   * 
   * @param filePath path of the workspace where the files are
   * @param jobNumber number of current job
   * @param results a string vector containing the plate simulation results 
   */
  static void report(const std::string& filePath, const std::string& jobNumber,
    std::vector<std::string> results);

  /**
   * @brief This method reports back to the tsv file, where it adds
   * all the resulting matrixes in binary files.
   * 
   * @param filePath path of the workspace where the files are
   * @param plate Plate to be writen
   */
  static void reportMatrix(const std::string& filePath, Plate_t& plate);

  /**
   * @brief Method to create the line that will be written in the
   * .tsv file
   * 
   * @param plate Structure that contains all the information to set in the
   * return string
   * @return string, returns the lines that will be written in the
   * file
   */
  std::string createResult(Plate_t& plate);
};

#endif  // REPORTER_
