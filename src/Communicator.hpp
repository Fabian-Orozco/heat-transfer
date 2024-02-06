// Copyright EsperaActiva

/**
 * @file Communicator.hpp
 * @brief Class implementing methods for communication using MPI technology for distributing work between nodes
 * @author Team EsperaActiva
 * @date 12/2021
 */
#ifndef COMMUNICATOR_
#define COMMUNICATOR_

#include <string>
#include <vector>

#include "BINRead.hpp"
#include "Reader.hpp"
#include "Reporter.hpp"
#include "Simulation.hpp"
#include "Plate.hpp"

class Communicator {
 public:
  /**
   * @brief Method to Broadcast all variables in the parameters from the
   * process 0
   * 
   * @param processNumber the current thread number
   * @param mythread_count the total ammount of threads
   * @param myFilePathSize size in chars, of the file path string
   * @param myFilePathChar a char* containing the file path
   * @param myFilePath string containing the file path
   * @param myJobNumberSize the Job Number size
   * @param myJobNumberChar char* containing the Job Number
   * @param myJobNumber  string containing the Job Number
   */
  static void broadcast(int& processNumber, int& mythread_count,
    int& myFilePathSize, char*& myFilePathChar, std::string& myFilePath,
    int& myJobNumberSize, char*& myJobNumberChar, std::string& myJobNumber);

  /**
   * @brief Method for the process 0 to recieve the results from every
   * other process
   * 
   * @param readyProcess the process that is sending back the results
   * @param currentResultLength the results' string size
   * @param results a string containing the work results
   * @return int returns this method's Exit Status
   */
  static int receiveResults(int& readyProcess, int& currentResultLength,
  std::vector<std::string>& results);

  /**
   * @brief Sends work from process 0 to all other processes
   * 
   * @param lines a string array containing the jobs
   * @param currentIndex position in the plates array for the current plate
   * @param readyProcess the target thead to send next plate work
   * @return int int return this method Exit Status 
   */
  static int sendWork(std::vector<std::string>& lines, size_t& currentIndex,
    int& readyProcess);

  /**
   * @brief Method for the process 0 to receive the last results from the
   * processes
   * 
   * @param readyProcess the process/node signaled as ready to process a job
   * @param currentResultLength the string size
   * @param results a string containing the results
   * @return int return this method Exit Status 
   */
  static int receiveLastResults(int& readyProcess, int& currentResultLength,
    std::vector<std::string>& results);

  /**
   * @brief Method to send the results from all processes to process 0
   * 
   * @param processNumber int identifying the thread that is executing a simulation
   * @param currentResult string for writing the results and send it to the process 0
   * @return int returns this method's Exit status
   */
  static int sendResults(int& processNumber, std::string& currentResult);

  /**
   * @brief Method for all processes to receive work from process 0
   * 
   * @param currentPlatePath path to the current job's plate
   * @param currentIndex position in the plates array for the current plate
   * @param myReader a reader object containing the current plate's jobfile information
   * @param myBinReader a BinReader object contaning the plate information
   * @param mySimulation simulation object used for this plate simulation
   * @param mythread_count number of threads requested this program execution
   * @param currentResult results from this plate simulation execution
   * @param myReporter a reporter object for writing the results 
   * @param myFilePath path to the file containing the job information
   * @return int 
   */
  static int receiveWork(char*& currentPlatePath, int& currentIndex,
    Reader& myReader, BINRead& myBinReader, Simulation& mySimulation,
    int& mythread_count, std::string& currentResult, Reporter& myReporter,
    std::string& myFilePath);
};

#endif  // COMMUNICATOR_
