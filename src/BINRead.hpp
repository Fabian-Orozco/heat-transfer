// Copyright EsperaActiva

/**
 * @file BINRead.hpp 
 * @brief Class in charge of reading binary files (arrays)
 * @author Team EsperaActiva
 * @date 11/2021
 */

#ifndef BINREAD_H
#define BINREAD_H

#include <fstream>
#include <string>

#include "Matrix.hpp"

class BINRead {
 private:
  int columns; /**< integer with the number of columns in the matrix**/
  int rows; /**< integer with the number of rows in the matrix**/
  std::ifstream archivo; /**< input stream (file to read)**/
  Matrix *matriz; /**< matrix where the binary information will be loaded**/

 public:
  /**
  * @brief Class constructor, initialize row column values to 0 and matrix pointer to nullptr.
  */
  BINRead();

  /**
  * @brief Class constructor, receives the address of the file to be opened to fill the array.
  * @details Read the number of column (c) and number of rows (f) parameters, then create the size matrix f * c. And then fill it with the corresponding values.
  * @param nombre represents a row containing the name of the file to read
  */
  void read(std::string nombre);

  /**
  * @brief Allows access to the matrix.
  * @return *Matrix returns an array with the loaded data
  */
  Matrix *getMatrix();
};
#endif  // BINREAD_H
