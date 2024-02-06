// Copyright EsperaActiva

/**
 * @file Reader.hpp 
 * @brief Class in charge of parsing arguments and reading files
 * @author Team EsperaActiva
 * @date 11/2021
 */

#ifndef READER_H
#define READER_H

#include <fstream>    // ifstream
#include <iostream>   // io
#include <stdexcept>  // invalid_argument
#include <string>
#include <vector>

#include "Plate.hpp"

class Reader {
 private:
  std::string jobFilename;  ///< name of the text file where the plates are**/
  std::string jobNumber;  ///< number of current job**/
  std::string filePath;  ///< path of the workspace where the files are**/
  std::vector<std::string> linesTextFile;  ///< vector that contains in rows
  ///< each line of the text file
 public:
  /**
  * @brief Class constructor
  */
  Reader();

  /**
  * @brief Returns the name of the job file 
  * @return string attribute with the name of the job file
  */
  std::string getJobFilename();

  /**
   * @brief Method to get access to a string vector containing each 
   * line from the text file (JobFile)
   * 
   * @return string vector containing said lines from the text file 
   */
  std::vector<std::string> getLinesTextFile();

  /**
  * @brief Returns the number of the job file 
  * @return int attribute with the number of the job file
  */
  std::string getJobNumber();

  /**
  * @brief Returns the name of file path
  * @return string attribute with the name of the file path
  */
  std::string getFilePath();

  /**
   * @brief validates the arguments given by the command line 
   * @details validates the filename if it is not provided, it issues an error message. In addition, it validates the number of execution threads (optional) by default the number of CPUs available in the system is used.
   * @param argc is the number of argument sent
   * @param argv[] it is the array that contains each argument
   * @param thread_count pointer to number of threads 
   * @param jobFile input file to be opened 
   * @remark if the file name is not provided an error will be given. The default number of threads will be the amount of cpus available.
   */
  void analyze_arguments(int argc, char* argv[], int& thread_count
    , std::ifstream& jobFile);

  /**
   * @brief divides the elements of a row and stores them in the variables sent by parameter respectively
   * @param line is where the data will be read and extracted
   * @param plate is a struct where the data of each plate is saved. 
   */
  void separate(std::string line, Plate_t& plate);

  /**
   * @brief performs the filling of each plate
   * @param plates vector that contains the plates struct
   */
  void fillPlateData(std::vector<Plate_t>& plates);

  /**
   * @brief Method to fill all the attributes on the plate structure
   * based on the line of the job file
   * 
   * @param line the line from the job file to be read
   * @param plate the structure where all information will be taken
   */
  void fillPlateStructure(std::string line, Plate_t& plate);

  /**
   * @brief loads the data from a file and stores it in an attribute (vector of strings, one field per line=
   * @param jobFile input stream, file to read from
   */
  void load_jobFile(std::ifstream& jobFile);

  /**
   * @brief Sets the file path attribute
   * 
   * @param filePath the file path that the attribute will be assigned to
   */
  void setFilePath(std::string& filePath);
};

#endif  // READER_H
