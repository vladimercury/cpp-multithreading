#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include "matrix.h"
#include "timer.h"

void printStats(double stats, int nCPU, const std::string mode, int chunkSize, Matrix matrixA, Matrix matrixB) {
    std::ofstream output;
    std::ostringstream fileName;
    fileName << "stats/" << nCPU;
    fileName << mode << chunkSize << "_";
    fileName << matrixA.rows << "x" << matrixA.cols << "_";
    fileName << matrixB.rows << "x" << matrixB.cols << ".txt";

    output.open(fileName.str(), std::ofstream::out | std::ofstream::app);
    output << " " << stats;
    output.close();
}

void countRow(int row, int width, const Matrix & first, const Matrix & second, Matrix & result) {
    for (int j = 0; j < result.cols; j++) {
        int sum = 0;
        for (int k = 0; k < width; k++) {
            sum += first.data[row][k] * second.data[k][j];
        }
        result.data[row][j] = sum;
    }
}

Matrix multiplyMatrixes(const Matrix & first, const Matrix & second, int nThreads = 1,
                        const std::string mode = "static", int chunkSize = 1) {
    if ((double)first.rows * second.cols > 1e7) {
        throw new std::runtime_error("Too big result matrix");
    }
    Matrix * result = new Matrix(first.rows, second.cols);
    int width = first.cols;
    if (nThreads > 1) {
        int ij, i, j, sum;
        if (mode.compare("dynamic") == 0) {
            #pragma omp parallel for private(ij, i, j, sum) num_threads(nThreads) schedule(dynamic,chunkSize)
            for (ij = 0; ij < result->rows * result->cols; ij++) {
                j = ij / result->rows;
                i = ij % result->cols;
                sum = 0;
                for (int k = 0; k < width; k++) {
                    sum += first.data[i][k] * second.data[k][j];
                }
                result->data[i][j] = sum;
            }
        } else if (mode.compare("guided") == 0) {
            #pragma omp parallel for private(ij, i, j, sum) num_threads(nThreads) schedule(guided,chunkSize)
            for (ij = 0; ij < result->rows * result->cols; ij++) {
                j = ij / result->rows;
                i = ij % result->cols;
                sum = 0;
                for (int k = 0; k < width; k++) {
                    sum += first.data[i][k] * second.data[k][j];
                }
                result->data[i][j] = sum;
            }
        } else {
            #pragma omp parallel for private(ij, i, j, sum) num_threads(nThreads) schedule(static)
            for (ij = 0; ij < result->rows * result->cols; ij++) {
                j = ij / result->rows;
                i = ij % result->cols;
                sum = 0;
                for (int k = 0; k < width; k++) {
                    sum += first.data[i][k] * second.data[k][j];
                }
                result->data[i][j] = sum;
            }
        }
    } else {
        for (int i = 0; i < result->rows; i++) {
            countRow(i, width, first, second, *result);
        }
    }
    return *result;
}

int main(int argc, char * argv[]) {
    int nCPU = atoi(argv[1]);
    std::string mode = argv[2];
    int chunkSize = atoi(argv[3]);
    std::string firstFile = argv[4];
    std::string secondFile = argv[5];

    Matrix matrixA, matrixB;
    try {
        matrixA.read("data/" + firstFile);
        matrixB.read("data/" + secondFile);
    } catch (std::exception * exc) {
        std::cout << exc->what() << std::endl;
        return -1;
    }
    if (matrixA.cols != matrixB.rows) {
        std::cout << "Matrixes don't fit each other";
        return -2;
    }

    Timer timer;
    Matrix result = multiplyMatrixes(matrixA, matrixB, nCPU, mode, chunkSize);
    double timeDelta = timer.getSecDelta();
    printf("%d CPUs %s %d %dx%d %dx%d: %.6f ms\n", nCPU, mode.c_str(), chunkSize,
           matrixA.rows, matrixA.cols, matrixB.rows, matrixB.cols, timeDelta);

    try {
        result.print("result.txt");
    } catch (std::exception * exc) {
        std::cout << exc->what() << std::endl;
        return -3;
    }
    printStats(timeDelta, nCPU, mode, chunkSize, matrixA, matrixB);
    return 0;
}