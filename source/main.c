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
   char * word_list[100]; // theoretical max number of words is also 10x10
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
      
      permute(word_list, 0, word_count-1);


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

void swap_index(char * array[], int index_a, int index_b){
    char * temp = array[index_a];
    array[index_a] = array[index_b];
    array[index_b] = temp;
    __asm("nop");    //debug breakpoint
}

void update_score (char * permutation[], size_t array_len){
   for(int i=0; i< array_len; i++)
      printf("%s ", permutation[i]);
   printf("\n");
}