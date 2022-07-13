#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OUTPUT_ROWS 10
#define OUTPUT_COLS 10

typedef struct{
   char output[OUTPUT_COLS][OUTPUT_ROWS];
   int words;
   int fill_level;
   int empty_cells;
   int first_empty_cell;
} packing_result_t;

int read_data(FILE * file, char buffer[], size_t buffer_len);
int str_comp_ascending(const void* a, const void *b);
int find_words(char input_buffer[], char * output_buffer[]);

void update_score(char * permutation[], size_t array_len);

void swap_index(char * array[],int index_a, int index_b);

void permute(char * input[], int current_index, int array_len);

void print_output(char buffer[OUTPUT_COLS][OUTPUT_ROWS]);

int count_empy_cells(char buffer[OUTPUT_COLS][OUTPUT_ROWS]);
#endif