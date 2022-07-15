#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

// global variable to store current best result
packing_result_t best_packing = {.words = 0, .fill_level = 100, .empty_cells = 0, .first_empty_cell=0};


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
    __asm("nop");    //debug breakpoint
}


void permute(char * input[], int current_index, int array_len) 
{  
   int i;
   if (current_index == array_len) 
      update_score(input, array_len+1);
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


void update_score (char * permutation[], size_t array_len){
   int word_index=0;
   int col_index=0;
   int row_index=0;

/*
   char current_packing[OUTPUT_ROWS][OUTPUT_COLS+1];             // create an "empty" output buffer
   char * current_string[OUTPUT_ROWS];
*/
   packing_result_t current_packing;
   initalize_output_buffer(&current_packing);

   int tmp = 0;      // this keeps count of the most amount of empty cells per line

   while(row_index<OUTPUT_ROWS && word_index < array_len){     // pack permutation of string into cells 
      char * word = permutation[word_index++];
      int word_len = strlen(word);
      
      int empty_space = OUTPUT_COLS - (col_index + word_len);
      if(empty_space < 0){
         row_index++;
         col_index = 0;
      } 

      memcpy(&current_packing.output[row_index][col_index], word, word_len);
      col_index += word_len;
   }

   int empty_space_count = 0;
   for(int i=0; i<OUTPUT_ROWS; i++){
      empty_space_count += count_empty_cells(current_packing.output[i], OUTPUT_COLS);
      current_packing.cummulative_empty_cells[i] = empty_space_count;

      if(best_packing.cummulative_empty_cells[i] < current_packing.cummulative_empty_cells[i])
         return;
   }

   memcpy(&best_packing, &current_packing, sizeof(best_packing)); // save curren packing as best packing
   return;
   /*
   int best_empty_cells = count_empty_cells(best_packing.output, sizeof(best_packing.output));
   int current_empty_cells = count_empty_cells(current_packing, sizeof(current_packing));


   if(best_empty_cells < current_empty_cells)

   for(int i=OUTPUT_ROWS-1; i >= 0; i--) {
      int current_row_empty_cells = count_empty_cells(&current_packing[i][0], OUTPUT_COLS);
      int best_row_empty_cells = count_empty_cells(&best_packing.output[i][0], OUTPUT_COLS);
      if(best_row_empty_cells < current_row_empty_cells)
         return;
   }

   memcpy(best_packing.output, current_packing, sizeof(best_packing.output));
*/
/*
   int current_empty_cells=count_empty_cells((const char*)current_packing, sizeof(current_packing));
   int current_first_empty_cell = strpbrk((const char *)current_packing, "+") - (char*)current_packing;
   */
   current_packing.words = word_index;
   current_packing.fill_level = row_index;
   if(
      (current_packing.words >= best_packing.words) &&          // if current packing has at least as many words as best
       (current_packing.fill_level <= best_packing.fill_level)     // and as good or lower fill level
//      && (current_empty_cells >= best_packing.empty_cells)  // and same ammount of empty cells or better 
      //&& (current_first_empty_cell > best_packing.first_empty_cell) // and first empty cell is higher
      ){
         int current_max_empty_cells = 0;
         /*
         for(int i=0; i < row_index; i++) {
            int current_row_empty_cells = count_empty_cells(&current_packing[i][0], OUTPUT_COLS);
            int best_row_empty_cells = count_empty_cells(&best_packing.output[i][0], OUTPUT_COLS);
            if(best_row_empty_cells < current_row_empty_cells)
               return;
         } 
         */
         memcpy(&best_packing, &current_packing, sizeof(best_packing)); // save curren packing as best packing
         /*
         best_packing.empty_cells = current_empty_cells;
         best_packing.words = word_index;
         best_packing.fill_level = row_index;
         best_packing.first_empty_cell = current_first_empty_cell;
         */
   }
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
/*
int count_empy_cells(char buffer[OUTPUT_COLS][OUTPUT_ROWS]){
   int count=0;
   for(int x=0; x<OUTPUT_ROWS; x++)
      for(int y=0; y<OUTPUT_COLS; y++)
         if(buffer[x][y]=='+')
            count++;
   return count;
}
*/

void initalize_output_buffer(packing_result_t * buffer){
   for(int i=0; i< OUTPUT_ROWS; i++){
      memset(buffer->output[i], '+', OUTPUT_COLS);
      buffer->output[i][OUTPUT_COLS] = '\0';
      buffer->lines[i] = buffer->output[i];
   }
   memset(buffer->cummulative_empty_cells, 100, sizeof(buffer->cummulative_empty_cells));
}
