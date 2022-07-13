#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int read_data(FILE * file, char buffer[], size_t buffer_len);
int str_len_comp(const char * a,const char *b);
int find_words(char input_buffer[], char * output_buffer[]);

#endif