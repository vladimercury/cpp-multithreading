#include "matrix.h"
#include <fstream>
#include <stdexcept>

Matrix::Matrix() {
    this->rows = 0;
    this->cols = 0;
    this->data = NULL;
}

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->allocate();
}

void Matrix::read(std::string fileName) {
    std::ifstream input(fileName);
    if (input.is_open()) {
        input >> this->rows >> this->cols;
        this->allocate();
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                input >> this->data[i][j];
            }
        }
        input.close();
    } else {
        throw new std::runtime_error("Input file not found");
    }
}

void Matrix::print(std::string fileName) {
    std::ofstream output(fileName);
    if (output.is_open()) {
        output << this->rows << " " << this->cols << std::endl;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                output << this->data[i][j] << " ";
            }
            output << std::endl;
        }
    } else {
        throw new std::runtime_error("Cannot open output file");
    }
}

void Matrix::allocate() {
    this->data = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->data[i] = new int[this->cols];
    }
}