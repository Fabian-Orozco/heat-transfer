// Copyright EsperaActiva
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "Calculator.hpp"
#include "Plate.hpp"
#include "Reporter.hpp"

std::string Reporter::createResult(Plate_t& plate) {
  std::string currentTimestamp;
  std::string result;
  currentTimestamp = Calculator::secondsToDate(
      plate.elapsedTime);
  result = plate.name+".bin  "+
    std::to_string(plate.time) +
    "  " + std::to_string(plate.thermal_diffusivity)
    + "  " + std::to_string(plate.dimensions)
    + "  " + std::to_string(plate.breakeven)
    + "  " + std::to_string(plate.kValue)
    +"  "+ currentTimestamp;
  return result;
}

void Reporter::report(const std::string& filePath,
  const std::string& jobNumber, std::vector<std::string> results) {
  std::ofstream jobFile;
  std::string jobFileName = filePath+"/tsv/"+"job"+jobNumber+".tsv";
  jobFile.open(jobFileName);
  for (size_t currentResult = 0; currentResult < results.size();
    ++currentResult) {
    jobFile << results[currentResult] << "\n";
  }
  jobFile.close();
}

void Reporter::reportMatrix(const std::string& filePath, Plate_t& plate) {
  std::ofstream matrixFile;
  std::string matrixFileName;
  Matrix* currentMatrix = nullptr;
  std::cout << "Plate number: " << plate.plateNumber << std::endl;
  matrixFileName+=filePath+"/tsv/"+plate.name
    +"-"+ std::to_string(plate.kValue) +".bin";
  matrixFile.open(matrixFileName, std::ios::app | std::ios::binary);
  currentMatrix = plate.matrix;
  size_t rows = currentMatrix->getRows();
  size_t columns = currentMatrix->getColumns();
  matrixFile.write(reinterpret_cast<char*>(&rows), sizeof(double));
  matrixFile.write(reinterpret_cast<char*>(&columns), sizeof(double));
  for (size_t row = 0; row < rows; ++row) {
    for (size_t column = 0; column < columns; ++column) {
      matrixFile.write(reinterpret_cast<char*>
        (&(*currentMatrix)[row][column]), sizeof(double));
    }
  }
  matrixFile.close();
  matrixFileName.clear();
  delete currentMatrix;
  currentMatrix = nullptr;
}
