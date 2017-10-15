#ifndef MULTITHREAD_TIMER_H
#define MULTITHREAD_TIMER_H

#include <sys/time.h>

class Timer {
    timeval timeMark;

public:
    Timer();
    void restart();
    double getSecDelta();
};

#endif //MULTITHREAD_TIMER_H
