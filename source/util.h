#ifndef UTIL_H
#define UTIL_H

#define OUTPUT_ROWS 10
#define OUTPUT_COLS 10

typedef struct{   
   char output[OUTPUT_ROWS][OUTPUT_COLS+1];
   char * lines[OUTPUT_ROWS];
   char cummulative_empty_cells[OUTPUT_ROWS];
   int words;
   int fill_level;
   int empty_cells;
   int first_empty_cell;
} packing_result_t;

extern packing_result_t best_packing;

/*
   Reads the file and sanitizes the data. Discards any byte that is not an ASCII
   upper or lower case character or a newline symbol.

   Inputs:
      file -         file pointer to an open file
      buffer -       array to store data into
      buffer_len -   max capacity of the buffer
   Outputs:
      returns '-1' on read error and number of bytes read otherwise. 
*/
int read_data(FILE * file, char buffer[], size_t buffer_len);

/*
   Splits the lines inside the input buffer into separate strings. NB! The data
   iside the input buffer will be used as the storege buffer of the strings and
   thus will be modified

   Inputs:
      input_buffer - buffer containing lines of text NB! must be NULL terminated
      output_buffer - array to store pointers to strings
   Output:
      returns number of words stored in output_buffer
*/
int find_words(char input_buffer[], char * output_buffer[]);

/*
   Swaps two char pointers inside an array by index.

   Inputs:
      array - array to perform swap on
      index_a, index_b - indecies to swap
*/
void swap_index(char * array[],int index_a, int index_b);

/*
   Evaluates the current permutation by fitting the strings in permutation order
   into a 10x10 grid and then evalutaing if the achieved packing is better than
   the previous best. If so the previous best is updated.

   Inputs:
      permutation - string pointers in order to try packing
      arrat_len - length of permutation
*/
void update_score(char * permutation[], size_t array_len);

/*
   Standard recursive permutaion algorithm to find all permutations of an 
   array of C-style string pointers - for each found permutation the update_score
   function is called and passed the permutation. After completion the best packing
   is stored in the "best_packing" struct.

   Inputs:
      input -  sequence of strings to permutate - an array of pointers to NULL 
               terminated strings
      current_index - tracks place in recursive function, set to 0 at beginning
      array_len - length of permutation, set to 1 less than the length of input 

*/
void permute(char * input[], int current_index, int array_len);

/*
   Convenience funtion to print the results.

   Input:
      buffer - the output buffer to print
*/
void print_output(char buffer[OUTPUT_ROWS][OUTPUT_COLS+1]);

/*
   Convenience funtion to count number of "empty" cells.

   Input:
      buffer - the output buffer to print
*/
//int count_empy_cells(char buffer[OUTPUT_COLS][OUTPUT_ROWS]);

int count_empty_cells(const char * buffer, size_t len);

//void initalize_output_buffer(char data_buffer[OUTPUT_ROWS][OUTPUT_COLS+1], char * string_buffer[OUTPUT_ROWS]);

void initalize_output_buffer(packing_result_t * buffer);

#endif