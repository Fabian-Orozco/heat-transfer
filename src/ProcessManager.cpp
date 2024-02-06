// Copyright Espera Activa
#include <mpi.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "BINRead.hpp"
#include "Communicator.hpp"
#include "Matrix.hpp"
#include "ProcessManager.hpp"
#include "Reader.hpp"
#include "Reporter.hpp"
#include "Simulation.hpp"

bool ProcessManager::getSmaller(std::string first, std::string second) {
  return (getIndex(first)) < (getIndex(second));
}

int ProcessManager::getIndex(std::string plateWithIndex) {
  int startIndex = plateWithIndex.find("p");
  return atoi(plateWithIndex.substr(0, startIndex).c_str());
}

int ProcessManager::start(int argc, char* argv[],
  const std::vector<std::string>& plateLines, int& thread_count,
  Reader& reader) {
  int error = EXIT_SUCCESS;
  int provided = -1;
  double start_time = 0.0;
  double elapsed_time = 0.0;
  if (MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided) ==
    MPI_SUCCESS) {
    int mythread_count;
    int myFilePathSize = -1;
    char* myFilePathChar = nullptr;
    std::string myFilePath;
    char* myJobNumberChar = nullptr;
    int myJobNumberSize = -1;
    std::string myJobNumber;
    // declare myBinReader;
    BINRead myBinReader;
    Reader myReader;
    // declare mySimulation;
    Simulation mySimulation;
    // declare myReporter
    Reporter myReporter;
    // get processNumber;
    // get processCount;
    int processNumber = -1;
    error = MPI_Comm_rank(MPI_COMM_WORLD, &processNumber);
    int processCount = -1;
    error = MPI_Comm_size(MPI_COMM_WORLD, &processCount);
    if (processNumber == 0) {
      start_time = MPI_Wtime();  // measures process wall time 0
      mythread_count = thread_count;
      myFilePath = reader.getFilePath();
      myFilePathSize = myFilePath.size();
      myJobNumber = reader.getJobNumber();
      myJobNumberSize = myJobNumber.size();
    }
    Communicator::broadcast(processNumber, mythread_count,
    myFilePathSize, myFilePathChar, myFilePath,
    myJobNumberSize, myJobNumberChar, myJobNumber);
    myReader.setFilePath(myFilePath);
    // iterate through the plates in the jobfile
    // if (processNumber equals 0) do
    if (processNumber == 0) {
      // process number that is ready to work
      // declare readyProcess as an integer
      int readyProcess = -1;
      int currentResultLength = -1;
      std::vector<std::string> lines;
      lines = plateLines;
      // declare array of results
      std::vector<std::string> results;
      // while (plateFile available) do
      for (size_t currentIndex = 0; currentIndex < plateLines.size();
        ++currentIndex) {
        error = Communicator::receiveResults(readyProcess, currentResultLength,
          results);
        error = Communicator::sendWork(lines, currentIndex, readyProcess);
      // end
      }
      // while (length(results) != length(plates)) do
      while (results.size() != plateLines.size()) {
        error = Communicator::receiveLastResults(readyProcess,
        currentResultLength, results);
      // end
      }
      // // stop condition is a -1 index like "-1plate"
      int stop = -1;
      for (int currentProcess = 1; currentProcess < processCount;
        ++currentProcess) {
        // send(-1, 1, all processes)
        if (MPI_Send(&stop,
          1, MPI_INT, currentProcess, 0,
          MPI_COMM_WORLD) != MPI_SUCCESS) {
          std::cerr << "could not send stop condition" << std::endl;
          error = EXIT_FAILURE;
        }
      }
      // sort(results)
      std::sort(results.begin(), results.end(), getSmaller);
      // myReporter report results
      myReporter.report(myFilePath, myJobNumber, results);

      elapsed_time = MPI_Wtime() - start_time;
      std::cout << "process " << processNumber << ", time elapsed to finalize: "
        << elapsed_time << "s" << std:: endl;
    } else {
      // end
      // else do
      // declare currentPlatePath
      char* currentPlatePath = nullptr;
      // declare currentIndex
      int currentIndex = -2;
      // declare currentResult
      std::string currentResult("empty");
      // while (currentIndex not equal -1) do
      while (currentIndex != -1) {
        error = Communicator::sendResults(processNumber, currentResult);
        error = Communicator::receiveWork(currentPlatePath, currentIndex,
        myReader, myBinReader, mySimulation, mythread_count, currentResult,
        myReporter, myFilePath);
      }
    }
    // end
    // end
    MPI_Finalize();
  }
  return error;
}
