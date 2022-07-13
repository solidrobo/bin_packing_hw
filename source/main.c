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

   const char *filename = argv[1];
   FILE * fp = fopen(filename, "r");
   char file_buffer[100];  // max number of characters to be displayed is 10x10
   char *word_list[100]; // theoretical max number of words is also 10x10
   size_t word_count=0;
   if(read_data(fp, file_buffer, sizeof(file_buffer))>0){ // populate buffer with sanitized data
      int row, col;
      char *word = strtok(file_buffer, "\n");
      do{
         size_t len = strlen(word);
         if(len > 10){
            printf("Word [%s] too long [%d]. Discarding...", word, len);
            break; 
         }

         word_list[word_count++] = word;

         printf("word %s\n", word);
         word = strtok(NULL, "\n");
      }while (word);

      for(int i = 0; i<word_count; i++){
         printf("% 3d word %s\n", i,word_list[i]);
      }

      qsort(word_list, word_count+1, sizeof(char*), str_len_comp);

      for(int i = 0; i<word_count; i++){
         printf("% 3d word %s\n", i,word_list[i]);
      }

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
            //buffer[i-1] = '\0'; // terminate buffer
            //read_bytes = i;
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


int str_len_comp(const char * a, const char *b){
   return strlen(a) > strlen(b);
}
