#ifndef FILE_COPY_H
#define FILE_COPY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MACROS 100
#define MAX_LINES_PER_MACRO 100
#define MAX_LINE_LENGTH 1024

typedef struct {
    char name[50];
    char content[MAX_LINES_PER_MACRO][MAX_LINE_LENGTH];
    int line_count;
} Macro;

void add_macro(const char *name, char content[MAX_LINES_PER_MACRO][MAX_LINE_LENGTH], int line_count);
Macro *find_macro(const char *name);
void remove_extra_spaces(char *line);
void pre_assembler(const char *filename);
const char *load_file(int argc, char *filename);
void check_the_file(const char *filename_ad);
int is_empty_line(const char *line);

#endif // FILE_COPY_H
