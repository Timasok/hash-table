#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

struct Timer
{
    __uint64_t st_time;
    __uint64_t stop_time;
};

Timer * launchTimer() __attribute__((always_inline));
int stopTimer(Timer ** timer) __attribute__((always_inline));

#endif