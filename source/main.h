#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
   char * word;
   size_t length;
}string_len_t;

int read_data(FILE * file, char buffer[], size_t buffer_len);
void insertionSort(string_len_t array[], int size);
int str_len_comp(const char * a,const char *b);


#endif