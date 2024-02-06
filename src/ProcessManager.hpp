// Copyright EsperaActiva

/**
 * @file ProcessManager.hpp 
 * @brief Class containing utility methods for extracting plate information,
 * creation of files and distribution of work
 * @author Team EsperaActiva
 * @date 12/2021
 */

#ifndef PROCESS_MANAGER_
#define PROCESS_MANAGER_

#include <string>
#include <vector>

#include <Plate.hpp>
#include "Reader.hpp"

class ProcessManager {
 private:
  /**
   * @brief Method to sort the results vector using the sort function from the
   * std library
   * 
   * @param first A string
   * @param second Another string to be compared with the first string
   * @return true if the first string goes before the second string
   * @return false if the second string is smaller and goes first
   */
  static bool getSmaller(std::string first, std::string second);

 public:
  /**
   * @brief Method that distributes work between the nodes and creates all
   * files
   * 
   * @param argc argument count
   * @param argv array of char containing all arguments received when executed
   * @param plateLines vector holding all request works in the JobFile
   * @param thread_count number of threads to execute in this program
   * @param reader Reader object holding JobFile information
   * @return int Returns this method's exit status
   */
  int start(int argc, char* argv[],
  const std::vector<std::string>& plateLines, int& thread_count,
  Reader& reader);
  /**
   * @brief Method to get a number from the plate file path
   * @details we add the index of the corresponding matrix at the start of
   * the plate path as follows "1plate00..."
   * 
   * @param plateWithIndex the string holding the index and name plate to be
   *  splited in two
   * @return int returns the extracted index from plateWithIndex
   */
  static int getIndex(std::string plateWithIndex);
};
#endif  // PROCESS_MANAGER_
