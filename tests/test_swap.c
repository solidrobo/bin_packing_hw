#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../source/util.h"

int main(   int argc, // Number of strings in array argv
            char *argv[],      // Array of command-line argument strings
            char **envp ){
    int status;

    char * a = "12";
    char * b = "21";

    char * test[2] = {a,b};

    swap_index(test, 0, 1);

    if(strcmp(test[0], "21") && strcmp(test[1], "12")){
        printf("String Index swap failed!\n");
        return -1;
    }

    
    return 0;
}