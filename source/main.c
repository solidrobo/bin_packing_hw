#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib.h"

int main(   int argc, // Number of strings in array argv
            char *argv[],      // Array of command-line argument strings
            char **envp ){

   char *filename;
   char *argument;
   /*
      Input validation section 
   */
   switch (argc){
      case 1:
         printf("Please provide filepath with optional argument -v for verbose output!\n");
         return -1;
      case 2:
         filename = argv[1];
         break;
      default:
         if(argv[1][0] == '-'){
            filename = argv[2];
            argument = argv[1];
         } else {
            filename = argv[1];
            argument = argv[2];
         }
         if(strcmp(argument, "-v") == 0){
            en_verbose_mode = 1;
         } else {
            printf("Warning! Unknown argument [%s]\n", argument);
         }
         break;
   }

   /*
      Variables section
   */

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

      if(en_verbose_mode)
         printf("Looking for best packing\n");

      permute(word_list, 0, word_count-1); // find best packing by testing all permutations

      if(en_verbose_mode)
         printf("\nFound packing!\n");

      print_output(best_packing.buffer);  // output best packing
      
   } else {
      return -1;
   }
   fclose(fp);
   return 0;
}