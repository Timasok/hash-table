#ifndef MODE_SPECS
#define MODE_SPECS

#define ALBUM 1
#define BOOK 2

#define H_TAB_DATA BOOK

#if H_TAB_DATA == ALBUM
const char * TEXT_DATA_PATH  = "data_files/Illmatic.txt";
const char * PROCESSED_DATA  = "data_files/Illmatic.pr";

#elif H_TAB_DATA == BOOK
const char * TEXT_DATA_PATH  = "data_files/LOTR.txt";
const char * PROCESSED_DATA  = "data_files/LOTR.pr";
#endif

const int MAX_STRING_LENGTH = 8;

#endif