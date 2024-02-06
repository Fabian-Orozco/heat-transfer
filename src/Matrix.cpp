// Copyright EsperaActiva
#include <iostream>
#include "Matrix.hpp"

Matrix::Matrix() {
  this->rows = 0;
  this->columns = 0;
}

Matrix::Matrix(size_t rows, size_t columns) {
  this->rows = rows;
  this->columns = columns;
  this->setMatrix();
}

Matrix::~Matrix() {
  if (!this->matrix.empty()) {
    this->matrix.clear();
  }
}

void Matrix::setRows(size_t rows) {
  this->rows = rows;
}

void Matrix::setColumns(size_t columns) {
  this->columns = columns;
}

void Matrix::setMatrix() {
  for (size_t currentRow = 0; currentRow < this->rows; ++currentRow) {
    std::vector<double> add(this->columns);
    this->matrix.push_back(add);
  }
}

size_t Matrix::getRows() {
  return this->rows;
}

size_t Matrix::getColumns() {
  return this->columns;
}

std::vector<double>& Matrix::operator[](size_t row) {
  return this->matrix[row];
}

void Matrix::print() {
  for (size_t row = 0; row < this->rows; ++row) {
    for (size_t column = 0; column < this->columns; ++column) {
      std::cout << this->matrix[row][column] << " ";
    }
    std::cout << std::endl;
  }
}

