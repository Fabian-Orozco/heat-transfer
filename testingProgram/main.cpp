// #include "Comparator.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include "../src/BINRead.hpp"
#include "../src/Matrix.hpp"
#include "../src/Reader.hpp"

bool platesEquals(Matrix* m_plate01, Matrix* m_plate02, int epsilon);

int main(int argc, char* argv[]) {
  BINRead binReader;  // para leer plates
  std::cout << std::endl;

  std::string plate01 = argv[1];
  std::cout << "plate01: " << plate01 << std::endl;
  std::string plate02 = argv[2];
  std::cout << "plate02: " << plate02 << std::endl;
  
  float epsilon = 0;
  if (argc == 4) {
     epsilon = std::stof(argv[3]);
  } else {
    std::cout << "\nerror: epsilon(sensitive) not provided" << std::endl;
    return 1;
  }
    std::cout << "epsilon: " << epsilon << std::endl;

  std::cout << std::endl;
  binReader.read(plate01);
  Matrix* m_plate01 = binReader.getMatrix();

  binReader.read(plate02);
  Matrix* m_plate02 = binReader.getMatrix();

  if (platesEquals(m_plate01, m_plate02, epsilon)) {
    std::cout << plate01 << " is equal to"  << plate02 << std::endl;
  } else {
    std::cout << plate01 << " is different to"  << plate02 << std::endl;
  }

  m_plate01->print();
  std::cout << std::endl;
  m_plate02->print();

  delete m_plate01;
  delete m_plate02;

  return 0;
}

bool platesEquals(Matrix* m_plate01, Matrix* m_plate02, int epsilon) {
  for (int row = 0; row < m_plate01->getRows(); ++row) {
    for (int column = 0; column < m_plate01->getColumns(); ++column) {
      if (std::abs((*m_plate01)[row][column] - (*m_plate02)[row][column]) > epsilon) {
        return false;
      }
    }
  }
  return true;
}
