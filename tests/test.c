#include <stdlib.h>
#include <stdio.h>

int main(   int argc, // Number of strings in array argv
            char *argv[],      // Array of command-line argument strings
            char **envp ){
    int status;
    fprintf(stderr, "running test %s\n", argv[1]);
    
    //int status = system(argv[1]);
    
    return 0;
}