#ifndef FILE_COPY_H
#define FILE_COPY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

typedef struct Macro {
    char *name;             // שם המקרו בזיכרון דינאמי
    char **content;         // מערך דינאמי של שורות המקרו
    int line_count;
    struct Macro *next;     // מצביע למקרו הבא ברשימה המקושרת
} Macro;

void add_macro(const char *name, char **content, int line_count);
Macro *find_macro(const char *name);
void remove_extra_spaces(char *line);
void pre_assembler(const char *filename);
char *load_file(char *filename);
void check_the_file(const char *filename_ad);
int is_empty_line(const char *line);
void free_macros(); // פונקציה לשחרור זיכרון של הרשימה המקושרת

#endif // FILE_COPY_H
