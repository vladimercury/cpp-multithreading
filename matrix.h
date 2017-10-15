#ifndef MULTITHREAD_MATRIX_H
#define MULTITHREAD_MATRIX_H

#include <string>

struct Matrix {
    int ** data;
    int rows;
    int cols;

    Matrix();
    Matrix(int rows, int cols);

    void read(std::string fileName);
    void print(std::string fileName);

private:
    void allocate();
};

#endif //MULTITHREAD_MATRIX_H
