#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

packing_result_t best_packing = {.words = 0, .fill_level = 100, .empty_cells = 0, .first_empty_cell=0};

int read_data(FILE * file, char buffer[], size_t buffer_len){
   size_t read_bytes = 0;
   if(file){   // check if file exixts
      do {  // read only the max number of characters able to be displayed 
         char data = fgetc(file);
         if( feof(file) ) {  // break if end of file reached
            buffer[read_bytes]='\0'; // terminate buffer
            break ;
         }
         
         if( (data>='a' && data<='z') || (data>='A' && data<='Z' || data == '\n')){  // sanitize input to contain only ASCII characters and line breaks
            buffer[read_bytes++] = data;
         }
         else
            __asm("nop"); // discard non ascii data / debug breakpoint
      }while(read_bytes < buffer_len);
   } else { // return error otherwise
      perror("Error reading file! ");
      return -1;
   }

   return read_bytes;
}

int find_words(char input_buffer[], char * output_buffer[]){
      size_t word_count=0;
      char *word = strtok(input_buffer, "\n");
      do{
         size_t len = strlen(word);
         if(len > 10 && len > 0){
            printf("Word [%s] too long [%d]. Discarding...", word, len);
            break; 
         }
         output_buffer[word_count++] = word;
         word = strtok(NULL, "\n");
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

   char current_packing[OUTPUT_ROWS][OUTPUT_COLS];
   memset(current_packing, '+', sizeof(current_packing));

   while(row_index<OUTPUT_ROWS && word_index < array_len){     // pack permutation of string into cells 
      char * word = permutation[word_index++];
      int word_len = strlen(word);
      
      if(col_index + word_len > OUTPUT_COLS){
         row_index++;
         col_index = 0;
      } 

      memcpy(&current_packing[row_index][col_index], word, word_len);
      col_index += word_len;
   }

   int current_empty_cells=count_empy_cells(current_packing);
   int current_first_empty_cell = strpbrk((const char *)current_packing, "+") - (char*)current_packing;
   if(
      (word_index >= best_packing.words) &&         // if current packing has at least as many words as best
      (row_index <= best_packing.fill_level) &&    // and as good or lower fill level
      (current_empty_cells >= best_packing.empty_cells) && // and same ammount of empty cells or better 
      (current_first_empty_cell > best_packing.first_empty_cell) 
      ){ // and first empty cell is higher
         memcpy(best_packing.output, current_packing, sizeof(best_packing.output)); // save curren packing as best packing
         best_packing.empty_cells = current_empty_cells;
         best_packing.words = word_index;
         best_packing.fill_level = row_index;
         best_packing.first_empty_cell = current_first_empty_cell;   
   }
}

void print_output(char buffer[OUTPUT_COLS][OUTPUT_ROWS]){
   for(int x = OUTPUT_ROWS-1; x>=0; x--){
      for(int y= 0; y<OUTPUT_COLS; y++){
         printf("%c", buffer[x][y]);
      }
      printf("\n");
   }
}

int count_empy_cells(char buffer[OUTPUT_COLS][OUTPUT_ROWS]){
   int count=0;
   for(int x=0; x<OUTPUT_ROWS; x++)
      for(int y=0; y<OUTPUT_COLS; y++)
         if(buffer[x][y]=='+')
            count++;
   return count;
}