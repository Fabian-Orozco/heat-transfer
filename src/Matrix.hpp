// Copyright EsperaActiva

/**
 * @file Matrix.hpp 
 * @brief Class representing a matrix
 * @author Team EsperaActiva
 * @date 11/2021
 */

#ifndef MATRIX_EA_
#define MATRIX_EA_

#include <vector>

class Matrix {
 private:
  std::vector<std::vector<double>> matrix;  /**< matrix structure**/
  size_t rows;  /**< the number of rows in the matrix**/
  size_t columns;  /**< the number of columns in the matrix**/

 public:
  /**
   * @brief Construct a new Matrix object
   * sets every attribute to 0
   * 
   */
  Matrix();
  /**
   * @brief Construct a new Matrix object
   * sets the rows and columns to the ones the were given
   * @param rows number of rows in the matrix
   * @param colums number of columns in the matrix
  */
  Matrix(size_t rows, size_t colums);
  /**
   * @brief Destroy the Matrix object
   */
  ~Matrix();

  /**
   * @brief set the number of rows with the parameter
   * @param rows number of rows
   */
  void setRows(size_t rows);

  /**
   * @brief set the number of colums with the parameter
   * @param colums number of colums
   */
  void setColumns(size_t colums);

  /**
   * @brief Method to declare the pointers of the matrix attribute
   * ONCE the rows and columns are set
   */
  void setMatrix();

  /**
   * @brief Method to obtain the rows
   * @return unsigned int with the number of rows
   */
  size_t getRows();

  /**
   * @brief Method to obtain the columns
   * @return unsigned int with the number of colums
   */
  size_t getColumns();

  /**
   * @brief Method to get the row of a matrix
   * @param row row of the matrix that wants to be accessed
   * @return std::vector<double>& row of the matrix that wants to be accessed
   */
  std::vector<double>& operator[](size_t row);

  /**
   * @brief Method to print the matrix.
   * The method will be used only by programers to test the program.
   */
  void print();
};
#endif  //  MATRIX_EA_
