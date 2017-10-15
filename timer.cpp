#include "timer.h"

Timer::Timer() {
    this->restart();
}

void Timer::restart() {
    gettimeofday(&this->timeMark, 0);
}

double Timer::getSecDelta() {
    timeval now;
    gettimeofday(&now, 0);
    return ((now.tv_sec - this->timeMark.tv_sec) * 1e6 + now.tv_usec - this->timeMark.tv_usec) / 1e6;
}