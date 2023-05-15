#include <stdio.h>
#include <stdlib.h>

#include "text_funcs.h"
#include "hash_funcs.h"
#include "htab_funcs.h"
#include "mode_specifics.h"
// #include "time_measure.h"

const char * mode_specs_file = "./config/mode_specifics.h";
const char * python_graphics = "./py_utils/graphics.py";
const char * python_stats = "./py_utils/statistics.py";

static const int NUMBER_OF_HASH_FUNCS = 7;

struct HF_info
{
    __uint32_t (*func_ptr)(const char *) = NULL;
    char * func_name = NULL;
    int plot_x_limit = 0;

};

static void fillHashFuncsArray(HF_info * hash_funcs_arr, int TAB_SIZE)
{
     hash_funcs_arr[0] = {.func_ptr = hash_1, .func_name = strdup("Const"), .plot_x_limit = 10};
     hash_funcs_arr[1] = {.func_ptr = hash_strlen, .func_name = strdup("Strlen"), .plot_x_limit = MAX_STRING_LENGTH+1};
     hash_funcs_arr[2] = {.func_ptr = hash_first_letter, .func_name = strdup("First_letter"), .plot_x_limit = 1<<8};
     hash_funcs_arr[3] = {.func_ptr = hash_ascii_sum, .func_name = strdup("Ascii_sum"), .plot_x_limit = (TAB_SIZE < 2000) ? TAB_SIZE : 2000};
     hash_funcs_arr[4] = {.func_ptr = hash_rotate_right, .func_name = strdup("Rotate_right"), .plot_x_limit = TAB_SIZE};
     hash_funcs_arr[5] = {.func_ptr = hash_rotate_left, .func_name = strdup("Rotate_left"), .plot_x_limit = TAB_SIZE};
     hash_funcs_arr[6] = {.func_ptr = hash_gnu, .func_name = strdup("GNU"), .plot_x_limit = TAB_SIZE};
};

static void destroyHashFuncsArray(HF_info * hash_funcs_arr)
{
    for(int i = 0; i < NUMBER_OF_HASH_FUNCS; i++)
        free(hash_funcs_arr[i].func_name);
};

struct Timer
{
    __uint64_t st_time;
    __uint64_t stop_time;
};

inline int launchTimer(Timer ** timer) __attribute__((always_inline));
inline int stopTimer(Timer ** timer) __attribute__((always_inline));

inline int launchTimer(Timer ** timer)
{
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

    return 0;

}

#define MEASURE_TIME(time_diff, oper, code)                               \
        Timer * timer = (Timer *)calloc(1, sizeof(Timer));          \
        launchTimer(&timer);                                        \
        code;                                                       \
        stopTimer(&timer);                                          \
        time_diff oper timer->stop_time - timer->st_time;        \
        free(timer);                                                \

int main(int argc, const char ** argv)
{
    // if(isNewer(mode_specifics, PROCESSED_DATA)); 
        // processData(TEXT_DATA_PATH, PROCESSED_DATA, MAX_STRING_LENGTH);

    __uint64_t time_diff = 0;
    MEASURE_TIME(time_diff, =, printf("\n\n\n\n\n\n\n"));
    printf("time = %lu\n", time_diff);


    // int TAB_SIZE = 5281;
    // int STR_LENGTH = 16;

    // if(argc>=2 && *(argv[1]))
    // {
    //     TAB_SIZE = atoi(argv[1]); 
    //     if(argc >= 2)
    //         STR_LENGTH = atoi(argv[2]);
    // }
    
    // HF_info  hash_funcs_arr[NUMBER_OF_HASH_FUNCS] = {};
    // fillHashFuncsArray(hash_funcs_arr, TAB_SIZE);
    // refreshStatFile();

    // for (int idx = 2; idx < NUMBER_OF_HASH_FUNCS; idx++)
    // {
    //     Hash_Table * tab = formTable(PROCESSED_DATA, TAB_SIZE, hash_funcs_arr[idx].func_ptr, STR_LENGTH);
    //     printf("=======wrds=cnt==%lu==========\n", tab->number_of_words);
    //     tableDtor(&tab);

    //     drawHistogram(python_graphics, hash_funcs_arr[idx].func_name, hash_funcs_arr[idx].plot_x_limit);

    // }
    // drawAnalysis(python_stats);
    
    // destroyHashFuncsArray(hash_funcs_arr);
}


// ".intel_syntax noprefix\n\t"
// ".att_syntax"
