// Copyright EsperaActiva
#include <iostream>
#include <fstream>
#include <string>

#include "BINRead.hpp"
#include "Matrix.hpp"

// Constructor
BINRead::BINRead() {
    columns = 0;
    rows = 0;
    matriz = nullptr;
}

// Lector
void BINRead::read(std::string nombre) {
  std::ifstream archivo;
  archivo.open(nombre, std::ios::binary);
  if (archivo) {
    size_t num = 0;

    // Castea 8 bits en un enterpara obtener las columnas.
    archivo.read(reinterpret_cast<char *>(&num), sizeof(double));
    rows = num;

    // Castea 8 bits en un enterpara obtener las filas.
    archivo.read(reinterpret_cast<char *>(&num), sizeof(double));
    columns = num;
    if (matriz) {
      matriz = nullptr;
    }
    matriz = new Matrix(rows, columns);  // Se crea la matriz.

    double valor = 0;

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        // Castea 8 bits en un double para rellenar la matriz.
        archivo.read(reinterpret_cast<char *>(&valor), sizeof(double));
        (*matriz)[i][j] = valor;
      }
    }
    archivo.close();
  } else {
      std::cerr << "error: <" << nombre << "> could not be opened" << std::endl;
      columns = 0;
      rows = 0;
    }
}
// Get que permite obtener la matriz del lector binario.
Matrix *BINRead::getMatrix() {
  return this->matriz;
}
