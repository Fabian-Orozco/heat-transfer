// Copyright Espera Activa
#include <mpi.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Communicator.hpp"
#include "ProcessManager.hpp"

void Communicator::broadcast(int& processNumber, int& mythread_count,
  int& myFilePathSize, char*& myFilePathChar, std::string& myFilePath,
  int& myJobNumberSize, char*& myJobNumberChar, std::string& myJobNumber) {
  if (MPI_Bcast(&mythread_count, /*count*/ 1, MPI_INT, /*root*/ 0
      , MPI_COMM_WORLD) != MPI_SUCCESS ) {
      std::cerr << "Broadcast error" << std::endl;
    }
    if (MPI_Bcast(&myFilePathSize, /*count*/ 1, MPI_INT, /*root*/ 0
      , MPI_COMM_WORLD) != MPI_SUCCESS ) {
      std::cerr << "Broadcast error" << std::endl;
    }
    myFilePathChar = new char[myFilePathSize];
    memset(myFilePathChar, 0, myFilePathSize);
    if (processNumber == 0) {
      // make a copy of the string
      snprintf(myFilePathChar, myFilePathSize+1, myFilePath.c_str());
    }
    if (MPI_Bcast(myFilePathChar, /*count*/ myFilePathSize,
      MPI_CHAR, /*root*/ 0
      , MPI_COMM_WORLD) != MPI_SUCCESS ) {
      std::cerr << "Broadcast error" << std::endl;
    }
    // set by hand, if not done by hand the char* is copied with junk
    for (int i = 0; i < myFilePathSize; ++i) {
      myFilePath += myFilePathChar[i];
    }
    delete [] myFilePathChar;
    if (MPI_Bcast(&myJobNumberSize, /*count*/ 1, MPI_INT, /*root*/ 0
      , MPI_COMM_WORLD) != MPI_SUCCESS ) {
      std::cerr << "Broadcast error" << std::endl;
    }
    myJobNumberChar = new char[myJobNumberSize];
    memset(myJobNumberChar, 0, myJobNumberSize);
    if (processNumber == 0) {
      // make a copy of the string
      snprintf(myJobNumberChar, myJobNumberSize+1, myJobNumber.c_str());
    }
    if (MPI_Bcast(myJobNumberChar, /*count*/ myJobNumberSize,
      MPI_CHAR, /*root*/ 0
      , MPI_COMM_WORLD) != MPI_SUCCESS ) {
      std::cerr << "Broadcast error" << std::endl;
    }
    // set by hand, if not done by hand the char* is copied with junk
    for (int i = 0; i < myJobNumberSize; ++i) {
      myJobNumber += myJobNumberChar[i];
    }
    delete [] myJobNumberChar;
}

int Communicator::receiveResults(int& readyProcess, int& currentResultLength,
  std::vector<std::string>& results) {
  if (MPI_Recv(&readyProcess, 1, MPI_INT, MPI_ANY_SOURCE, 0,
    MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
    std::cerr << "could not receive ready process" << std::endl;
    return EXIT_FAILURE;
  }
  if (MPI_Recv(&currentResultLength, 1, MPI_INT, readyProcess, 0,
    MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
    std::cerr << "could not receive current result length" << std::endl;
    return EXIT_FAILURE;
  }
  // receive(result, size(result), readyProcess)
  char* receivedResult = new char[currentResultLength];
  if (MPI_Recv(receivedResult, currentResultLength,
    MPI_CHAR, readyProcess, 0, MPI_COMM_WORLD,
    MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
    std::cerr << "could not receive result" << std::endl;
    return EXIT_FAILURE;
  }
  std::string result(receivedResult);
  delete[] receivedResult;
  // if (result != "empty") do
  if (result != "empty") {
    // pushBack result to results
    results.push_back(result);
  }
  // end
  return EXIT_SUCCESS;
}

int Communicator::sendWork(std::vector<std::string>& lines,
  size_t& currentIndex, int& readyProcess) {
  // pushFront current_index to platePath
  lines[currentIndex].insert(0, std::to_string(currentIndex));
  // send(platePath, platePath_size, readyProcess)
  int currentPlateLineSize = lines[currentIndex].size();
  if (MPI_Send(&currentPlateLineSize,
    1, MPI_INT, readyProcess, 0,
    MPI_COMM_WORLD) != MPI_SUCCESS) {
    std::cerr << "could not send current plate line size" << std::endl;
    return EXIT_FAILURE;
  }
  if (MPI_Send(&(lines[currentIndex])[0],
    lines[currentIndex].size(), MPI_CHAR, readyProcess, 0,
    MPI_COMM_WORLD) != MPI_SUCCESS) {
    std::cerr << "could not send plate lines" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int Communicator::receiveLastResults(int& readyProcess,
  int& currentResultLength,
  std::vector<std::string>& results) {
  // receive(readyProcess, 1, any_process)
  // receive(result, size(result), readyProcess)
  if (MPI_Recv(&readyProcess, 1, MPI_INT, MPI_ANY_SOURCE, 0,
    MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
    std::cerr << "could not receive ready process" << std::endl;
      return EXIT_FAILURE;
  } else {
    if (MPI_Recv(&currentResultLength, 1, MPI_INT, readyProcess, 0,
      MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      std::cerr << "could not receive result length" << std::endl;
      return EXIT_FAILURE;
    }
    char* receivedResult = new char[currentResultLength];
    if (MPI_Recv(receivedResult, currentResultLength,
      MPI_CHAR, readyProcess, 0, MPI_COMM_WORLD,
      MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      std::cerr << "could not receive result" << std::endl;
      return EXIT_FAILURE;
    }
    // pushBack result to results
    std::string result(receivedResult);
    delete[] receivedResult;
    results.push_back(result);
  }
  return EXIT_SUCCESS;
}

int Communicator::sendResults(int& processNumber, std::string& currentResult) {
  // send(processNumber, 1, 0)
  if (MPI_Send(&processNumber,
    1, MPI_INT, 0, 0,
    MPI_COMM_WORLD) != MPI_SUCCESS) {
    std::cerr << "could not send process number" << std::endl;
    return EXIT_FAILURE;
  }
  int currentResultSize = currentResult.size();
  if (MPI_Send(&currentResultSize,
    1, MPI_INT, 0, 0,
    MPI_COMM_WORLD) != MPI_SUCCESS) {
    std::cerr << "could not current send result size" << std::endl;
    return EXIT_FAILURE;
  }
  // send(currentResult, size(currentResult), 0)
  if (MPI_Send(&(currentResult[0]),
    currentResultSize, MPI_CHAR, 0, 0,
    MPI_COMM_WORLD) != MPI_SUCCESS) {
    std::cerr << "could not send current result" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
int Communicator::receiveWork(char*& currentPlatePath, int& currentIndex,
  Reader& myReader, BINRead& myBinReader, Simulation& mySimulation,
  int& mythread_count, std::string& currentResult, Reporter& myReporter,
  std::string& myFilePath) {
  // receive(currentPlatePath, 1, 0)
  int currentPlateSize = -1;
  if (MPI_Recv(&currentPlateSize, 1,
    MPI_INT, 0, 0, MPI_COMM_WORLD,
    MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
    std::cerr << "could not receive current plate size" << std::endl;
    return EXIT_FAILURE;
  }
  if (currentPlateSize != -1) {
    currentPlatePath = new char[currentPlateSize];
    if (MPI_Recv(currentPlatePath, currentPlateSize,
      MPI_CHAR, 0, 0, MPI_COMM_WORLD,
      MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      std::cerr << "could not receive current plate path" << std::endl;
      return EXIT_FAILURE;
    }
    std::string stringCurrentPath(currentPlatePath);
    delete[] currentPlatePath;
    currentPlatePath = nullptr;
    std::string currentPath;
    // extract currentIndex from currentPlatePath
    currentIndex = ProcessManager::getIndex(stringCurrentPath);
    currentPath = stringCurrentPath.substr(stringCurrentPath.find("p"));
    // if (current_index != -1) do
    Plate_t plate;
    myReader.fillPlateStructure(currentPath, plate);
    // myBinReader reads file and creates matrix
    myBinReader.read(plate.platePath);
    // mySimulation simulatesMatrix
    mySimulation.setMatrix(myBinReader.getMatrix());
    plate.elapsedTime = mySimulation.start(plate.time,
      plate.thermal_diffusivity,
      plate.dimensions, plate.breakeven, mythread_count,
      plate.kValue);
    plate.matrix = mySimulation.getPrevMatrix();
    delete mySimulation.getCurrentMatrix();
    // create string result
    currentResult.clear();
    currentResult =  myReporter.createResult(plate);
    // myReporter report matrix
    myReporter.reportMatrix(myFilePath, plate);
  // end
  } else {
    currentIndex = -1;
  }
  return EXIT_SUCCESS;
}
