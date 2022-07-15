#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

// global variable to store current best result
packing_result_t best_packing;
int en_verbose_mode = 0;

int read_data(FILE * file, char buffer[], size_t buffer_len){
   size_t read_bytes = 0;
   if(file){   // check if file exixts
      do {  // read only the max number of characters able to be displayed 
         char data = fgetc(file);
         if( feof(file) ) {  // break if end of file reached
            break ;
         }
         
         if( (data>='a' && data<='z') || (data>='A' && data<='Z' || data == '\n')){  // sanitize input to contain only ASCII characters and line breaks
            buffer[read_bytes++] = data;
         }
         else{
            buffer[read_bytes++] = '?';
         }
      }while(read_bytes < buffer_len);

      buffer[read_bytes]='\0'; // terminate buffer
   } else { // return error otherwise
      perror("Error reading file! ");
      return -1;
   }

   return read_bytes;
}


int find_words(char input_buffer[], char * output_buffer[]){
      int word_count=0;
      int total_length = 0;
      char *word = strtok(input_buffer, "\n");  // split string into lines
      do{
         size_t len = strlen(word);
         total_length+=len;
         if( 0 < len > 10){         // check that line found is not empty or too long
            printf("Word [%s] too long [%d]. Discarding...\n", word, len);
         } else if (strchr(word, '?')){ // check that word doesn't contain illegal characters
            printf("Word [%s] contains illegal characters!. Discarding...\n", word);
         } else
            output_buffer[word_count++] = word;    // store word
         word = strtok(NULL, "\n");

         if(total_length > OUTPUT_COLS*OUTPUT_ROWS){ // do not add more words than can be theoretically displayed
            printf("Total length of words [%d] exceeds cell capacity[%d]!. Discarding rest of words...\n", total_length, OUTPUT_COLS*OUTPUT_ROWS);
            break;
         }

      }while (word);

      return word_count;
}


void swap_index(char * array[], int index_a, int index_b){
   char * temp = array[index_a];
   array[index_a] = array[index_b];
   array[index_b] = temp;
}


void permute(char * input[], int current_index, int array_len) 
{  
   int i;
   if (current_index == array_len) {
      update_score(input, array_len+1);
   }
   else
   { 
      for (i = current_index; i <= array_len; i++) 
      { 
         swap_index(input,current_index, i); 
         permute(input, current_index+1, array_len); 
         swap_index(input,current_index, i); 
      } 
   } 
}

clock_t prev_time_sec;
unsigned long long permutation_count = 0;
unsigned long long total_permutations = 1;
void update_score (char * permutation[], size_t array_len){
   int word_index=0;
   int col_index=0;
   int row_index=0;

   packing_result_t current_packing;
   initalize_output_buffer(&current_packing);

   if(en_verbose_mode){
      if(total_permutations == 1)
         for(int i=1;i < array_len+1;i++)
            total_permutations *= i;
      permutation_count++;
      clock_t current_time_sec = clock() / CLOCKS_PER_SEC;
      clock_t time_diff = current_time_sec - prev_time_sec;
      if(current_time_sec - prev_time_sec > 0 || 
         permutation_count == total_permutations){
         printf("\r%u / %u\r", permutation_count,total_permutations);
         prev_time_sec = current_time_sec;
      }
   }

   while(row_index<OUTPUT_ROWS && word_index < array_len){     // pack permutation of string into cells 
      char * word = permutation[word_index++];
      int word_len = strlen(word);
      
      int empty_space = OUTPUT_COLS - (col_index + word_len);
      if(empty_space < 0){
         row_index++;
         col_index = 0;
      } 

      memcpy(&current_packing.buffer[row_index][col_index], word, word_len);
      col_index += word_len;
   }

   int empty_space_count = 0;
   for(int i=0; i<OUTPUT_ROWS; i++){      // calculate cummulative empty cells per row
      empty_space_count += count_empty_cells(current_packing.buffer[i], OUTPUT_COLS);
      current_packing.cummulative_empty_cells[i] = empty_space_count;

      if(best_packing.cummulative_empty_cells[i] 
            < current_packing.cummulative_empty_cells[i])  // compare current score to best and abort if current score is worse than it
         return;
   }

   memcpy(&best_packing, &current_packing, sizeof(best_packing)); // save current packing as best packing
}


void print_output(char buffer[OUTPUT_ROWS][OUTPUT_COLS+1]){
   for(int x = OUTPUT_ROWS-1; x>=0; x--){
      for(int y= 0; y<OUTPUT_COLS; y++){
         printf("%c", buffer[x][y]);
      }
      printf("\n");
   }
}

int count_empty_cells(const char * buffer, size_t len){
   int count=0;
   for(int i=0; i<len; i++)
      if(buffer[i] == '+')
         count++;
   return count;
}

void initalize_output_buffer(packing_result_t * object){
   for(int i=0; i< OUTPUT_ROWS; i++){
      memset(object->buffer[i], '+', OUTPUT_COLS);
      object->buffer[i][OUTPUT_COLS] = '\0';
      object->lines[i] = object->buffer[i];
   }
   memset(object->cummulative_empty_cells, 100, sizeof(object->cummulative_empty_cells));
}
