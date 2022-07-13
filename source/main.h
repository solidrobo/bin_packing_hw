#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
   char * str;
   size_t len;
} String_t;

int read_data(FILE * file, char buffer[], size_t buffer_len);
int str_comp_ascending(const void* a, const void *b);
int find_words(char input_buffer[], char * output_buffer[]);

void update_score(char * permutation[], size_t array_len);

void swap_index(char * array[],int index_a, int index_b);

void permute(char * input[], int current_index, int array_len);
#endif