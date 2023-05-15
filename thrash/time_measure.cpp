// #include <windows.h>
// #include <tchar.h>
#include "time_measure.h"

#include <stdio.h>
#include <stdlib.h>

struct Timer
{
    __uint64_t st_time;
    __uint64_t stop_time;
};

inline int launchTimer(Timer ** timer) __attribute__((always_inline));
inline int stopTimer(Timer ** timer) __attribute__((always_inline));

inline int launchTimer(Timer ** timer)
{
    *timer = (Timer *)calloc(1, sizeof(Timer));

        // ".intel_syntax noprefix\n\t"
        // ".att_syntax"

    asm volatile (   
        "rdtsc\n\t"
        "shl \t$32, %%rdx\n\t"
        "or \t%%rdx, %0\n\t"
        : "=a" ((*timer)->st_time)
        :
        : "rdx");

    return 0;
}

inline int stopTimer(Timer ** timer)
{       
    asm volatile (   
        "rdtsc\n\t"
        "shl \t$32, %%rdx\n\t"
        "or \t%%rdx, %0\n\t"
        : "=a" ((*timer)->stop_time)
        :
        : "rdx");

    printf("time = %lu\n", (*timer)->stop_time - (*timer)->st_time);
    free(*timer);

    return 0;

}