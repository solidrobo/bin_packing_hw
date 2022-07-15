#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"

int main(   int argc, // Number of strings in array argv
            char *argv[],      // Array of command-line argument strings
            char **envp ){

   /*
      Input validation section 
   */

   if(argc > 2){
      printf("Illegal number of arguments [%d]. Please pass only the file path as an argument");
      return -1;
   }

   /*
      Variables section
   */

   const char *filename = argv[1];
   FILE * fp = fopen(filename, "r");
   char file_buffer[OUTPUT_ROWS*OUTPUT_COLS*2];  // max number of characters to be displayed is 10x10 + up to 100 line endings
   char * word_list[OUTPUT_ROWS*OUTPUT_COLS]; // theoretical max number of words is also 10x10
   size_t word_count=0;

   /*
      Logic section
   */

   if(read_data(fp, file_buffer, sizeof(file_buffer))>0){ // populate buffer with sanitized data
      int row, col;
      
      word_count = find_words(file_buffer, word_list); // find all words from buffer
      if(! (word_count)> 0){
         printf("No words found!\n");
         return -1;
      }

      initalize_output_buffer(&best_packing); // initalize the output to be "empty"

      permute(word_list, 0, word_count-1); // find best packing by testing all permutations

      print_output(best_packing.output);  // output best packing
      
   } else {
      return -1;
   }
   fclose(fp);
   return 0;
}