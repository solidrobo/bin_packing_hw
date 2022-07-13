#include "main.h"



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
   char file_buffer[100];  // max number of characters to be displayed is 10x10
   String_t word_list[100]; // theoretical max number of words is also 10x10
   size_t word_count=0;

   /*
      Logic section
   */

   if(read_data(fp, file_buffer, sizeof(file_buffer))>0){ // populate buffer with sanitized data
      int row, col;
      
      word_count = find_words(file_buffer, word_list);
      if(! (word_count)> 0){
         printf("No words found!\n");
         return -1;
      }

      qsort(word_list, word_count, sizeof(word_list[0]), str_comp_ascending); // sort strings according to length

      for(int x =10; x; x--){
         for(int y=10; y; y--){
            printf("+");
         }
         printf("\n");
      }
      
   } else {
      printf("Error reading file!\n");
      return -1;
   }
   fclose(fp);
   return 0;
}

int read_data(FILE * file, char buffer[], size_t buffer_len){
   size_t read_bytes = 0;
   if(file){   // check if file exixts
      do {  // read only the max number of characters able to be displayed 
         char data = fgetc(file);
         if( feof(file) ) {  // break if end of file reached
            buffer[read_bytes]=NULL; // terminate buffer
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

int find_words(char input_buffer[], String_t output_buffer[]){
      size_t word_count=0;
      char *word = strtok(input_buffer, "\n");
      do{
         size_t len = strlen(word);
         if(len > 10 && len > 0){
            printf("Word [%s] too long [%d]. Discarding...", word, len);
            break; 
         }
         String_t * string = &output_buffer[word_count++];
         string->str = word;
         string->len = strlen(word);

         word = strtok(NULL, "\n");
      }while (word);

      return word_count;
}

int str_comp_ascending(const void * a, const void *b){
   size_t str_a_len = ((String_t *) a)->len;
   size_t str_b_len = ((String_t *) b)->len;

   if(str_a_len > str_b_len){
      return -1;
   } 
   if(str_a_len < str_b_len){
      return 1;
   }
   return 0;
}
