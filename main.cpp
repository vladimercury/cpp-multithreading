#include <iostream>
#include <cmath>
#include <sys/time.h>

int main() {
    const int N = int(1e+8);
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
       double a = sqrt(i) * sqrt(i + 1);
    }
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec - begin.tv_sec) * 1e6 + end.tv_usec - begin.tv_usec) / 1e6;
    std::cout << delta << std::endl;
    return 0;
}