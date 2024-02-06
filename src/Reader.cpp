// Copyright EsperaActiva
#include "Reader.hpp"

#include <unistd.h>  // nprocessors
#include <filesystem>  // path
#include <vector>

Reader::Reader() {
  jobFilename = "";
  jobNumber = -1;
  filePath = "";
}

std::string Reader::getJobFilename() {
  return this->jobFilename;
}

std::string Reader::getJobNumber() {
  return this->jobNumber;
}

std::string Reader::getFilePath() {
  return this->filePath;
}

std::vector<std::string> Reader::getLinesTextFile() {
  return this->linesTextFile;
}

void Reader::analyze_arguments(int argc, char* argv[], int& thread_count
  , std::ifstream& jobFile) {
  int errorjobFilename = 0;
  thread_count = sysconf(_SC_NPROCESSORS_ONLN);

  if (argc > 1) {  // valid argc
    // assign the read file
    this->jobFilename = argv[1];
    jobNumber = jobFilename.substr(jobFilename.find("txt")-4, 3);
    jobFile.open(jobFilename);

    if (!jobFile) {
      std::cout << argv[1] << std::endl;
      throw std::invalid_argument("error: job file name not provided\n");
      errorjobFilename = 1;
    }
  } else {  // invalid argc (only one / program name)
      throw std::invalid_argument("there are not enough arguments to start" \
      " the program.\n");
      errorjobFilename = 1;
  }

  if (!errorjobFilename && argc > 2) {
    // loads the data from a file and stores it in an attribute
    load_jobFile(jobFile);
    if (atoi(argv[2]) && atoi(argv[2]) > 0) {  // es tc
      thread_count = atoi(argv[2]);
    } else {
      std::filesystem::path path(argv[2]);
      if (std::filesystem::is_directory(path)) {
        this->filePath = argv[2];
      } else {
        throw std::invalid_argument("invalid file directory.\n");
      }
    }
  }
  if (!errorjobFilename && argc > 3) {
    std::filesystem::path path(argv[3]);
      if (std::filesystem::is_directory(path)) {
        this->filePath = argv[3];
      } else {
        throw std::invalid_argument("invalid file directory.\n");
      }
  }
}

void Reader::separate(std::string line, Plate_t& plate) {
  std::string temp;
  int taken = 0;
  size_t i = 0;
  while (i < line.length()) {
    while (line[i] == ' ' && i < line.length()) {
      ++i;
    }
    while (line[i] != ' ' && i < line.length() &&
      line[i] != '\t') {
      temp += line[i];
      ++i;
    }
    switch (taken) {
      case 0:
        plate.platePath = this->filePath + "/" + temp;
        plate.name = temp.substr(0, 8);
        plate.plateNumber = temp.substr(5, 3);
        temp.clear();
        ++taken;
       break;

      case 1:
        plate.time = stod(temp);
        temp.clear();
        ++taken;
       break;

      case 2:
        plate.thermal_diffusivity = stod(temp);
        temp.clear();
        ++taken;
       break;

      case 3:
        plate.dimensions = stod(temp);
        temp.clear();
        ++taken;
       break;

      case 4:
        plate.breakeven = stod(temp);
        temp.clear();
        ++taken;
       break;
    }
  }
}

void Reader::load_jobFile(std::ifstream& jobFile) {
  std::string current;
  while (!jobFile.eof()) {
    getline(jobFile, current);
    linesTextFile.push_back(current);
  }
  linesTextFile.pop_back();  // hace pop del salto de linea
}

void Reader::fillPlateData(std::vector<Plate_t>& plates) {
  for (size_t currentLine = 0; currentLine < linesTextFile.size();
    ++currentLine) {
    separate(linesTextFile[currentLine], plates[currentLine]);
  }
}

void Reader::fillPlateStructure(std::string line, Plate_t& plate) {
  separate(line, plate);
}

void Reader::setFilePath(std::string& filePath) {
  this->filePath = filePath;
}
