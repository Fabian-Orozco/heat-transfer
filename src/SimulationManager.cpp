// Copyright EsperaActiva

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "SimulationManager.hpp"
#include "BINRead.hpp"
#include "Matrix.hpp"
#include "Plate.hpp"
#include "ProcessManager.hpp"
#include "Reader.hpp"
#include "Reporter.hpp"
#include "Simulation.hpp"

void SimulationManager::start(int argc, char* argv[]) {
  int thread_count = 0;
  std::ifstream jobFile;
  Reader reader;
  try {
    reader.analyze_arguments(argc, argv, thread_count, jobFile);
    // Call Analyze to get the values of .txt
  }
  catch(const std::invalid_argument& e) {
    std::cerr << "error: invalid_arguments" << std::endl;
  }
  ProcessManager manager;
  manager.start(argc, argv, reader.getLinesTextFile(), thread_count, reader);
}
