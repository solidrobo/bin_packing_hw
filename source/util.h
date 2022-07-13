#ifndef UTIL_H
#define UTIL_H

#define OUTPUT_ROWS 10
#define OUTPUT_COLS 10

typedef struct{
   char output[OUTPUT_COLS][OUTPUT_ROWS];
   int words;
   int fill_level;
   int empty_cells;
   int first_empty_cell;
} packing_result_t;

extern packing_result_t best_packing;

int read_data(FILE * file, char buffer[], size_t buffer_len);
int find_words(char input_buffer[], char * output_buffer[]);
void swap_index(char * array[],int index_a, int index_b);
void update_score(char * permutation[], size_t array_len);
void permute(char * input[], int current_index, int array_len);
void print_output(char buffer[OUTPUT_COLS][OUTPUT_ROWS]);
int count_empy_cells(char buffer[OUTPUT_COLS][OUTPUT_ROWS]);

#endif