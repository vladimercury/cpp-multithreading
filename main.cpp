#include <iostream>
#include <fstream>
#include <cmath>
#include <sys/time.h>
#include <sstream>

struct Matrix {
    int ** data;
    int rows;
    int cols;

    Matrix() {
        this->rows = 0;
        this->cols = 0;
        this->data = NULL;
    }

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        this->data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            this->data[i] = new int[cols];
        }
    }
};

Matrix readMatrixFromFile(std::string fileName) {
    int rows, cols;
    Matrix * matrix;
    std::ifstream input(fileName);
    if (input.is_open()) {
        input >> rows >> cols;
        matrix = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                input >> matrix->data[i][j];
            }
        }
        input.close();
    } else {
        matrix = new Matrix();
    }
    return *matrix;
}

void printMatrixToFile(Matrix matrix, std::string fileName) {
    std::ofstream output(fileName);
    output << matrix.rows << " " << matrix.cols << std::endl;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            output << matrix.data[i][j] << " ";
        }
        output << std::endl;
    }
}

void printStatsToFile(double stats, int nCPU) {
    std::ofstream output;
    std::ostringstream fileName;
    fileName << "stats/" << nCPU << ".txt";

    output.open(fileName.str(), std::ofstream::out | std::ofstream::app);
    output << " " << stats;
    output.close();
}

Matrix multiplyMatrixes(Matrix & first, Matrix & second, int nThreads = 1) {
    Matrix * result = new Matrix(first.rows, second.cols);
    int width = first.cols;
    #pragma omp parallel for num_threads(nThreads)
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {
            int sum = 0;
            for (int k = 0; k < width; k++) {
                sum += first.data[i][k] * second.data[k][j];
            }
            result->data[i][j] = sum;
        }
    }
    return *result;
}

timeval timeStamp;

void setNewTimeStamp() {
    gettimeofday(&timeStamp, NULL);
}

double getTimeDelta() {
    timeval now;
    gettimeofday(&now, NULL);
    return ((now.tv_sec - timeStamp.tv_sec) * 1e6 + now.tv_usec - timeStamp.tv_usec) / 1e3;
}

int main(int argc, char * argv[]) {
    int nCPU = 1;
    if (argc > 1) {
        nCPU = atoi(argv[1]);
    }

    Matrix matrixA, matrixB;
    matrixA = readMatrixFromFile("1.txt");
    matrixB = readMatrixFromFile("2.txt");
    if (matrixA.cols != matrixB.rows) {
        std::cerr << "Matrixes don't fit each other";
        return -1;
    }

    setNewTimeStamp();
    Matrix result = multiplyMatrixes(matrixA, matrixB, nCPU);
    double timeDelta = getTimeDelta();
    printf("%d CPUs: %.6f ms\n", nCPU, timeDelta);

    printMatrixToFile(result, "result.txt");
    printStatsToFile(timeDelta, nCPU);
    return 0;
}