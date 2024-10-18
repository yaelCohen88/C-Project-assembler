#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/utils.h"

Macro macros[MAX_MACROS];
int macro_count = 0;

// הוספת מקרו לטבלה
void add_macro(const char *name, char content[MAX_LINES_PER_MACRO][MAX_LINE_LENGTH], int line_count) {
    if (macro_count < MAX_MACROS) {
        strncpy(macros[macro_count].name, name, sizeof(macros[macro_count].name));
        macros[macro_count].line_count = line_count;
        for (int i = 0; i < line_count; i++) {
            strncpy(macros[macro_count].content[i], content[i], MAX_LINE_LENGTH);
        }
        macro_count++;
    }
}

// חיפוש מקרו לפי שם
Macro *find_macro(const char *name) {
   
    for (int i = 0; i < macro_count; i++) {
        
        if (strncmp(macros[i].name, name ,strlen(macros[i].name) ) == 0) {
            return &macros[i];
        }
    }
    return NULL;
}

// הסרת רווחים מיותרים משורה
void remove_extra_spaces(char *line) {
    int j = 0;
    int in_space = 0;
    int i = 0;

    while (line[i] == ' ') {
        i++;
    }

    for (; line[i] != '\0'; i++) {
        if (line[i] != ' ') {
            line[j++] = line[i];
            in_space = 0;
        } else if (!in_space) {
            line[j++] = ' ';
            in_space = 1;
        }
    }
    line[j] = '\0';
}

int is_empty_line(const char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return 0; // השורה אינה ריקה
        }
        line++;
    }
    return 1; // השורה ריקה או מכילה רק רווחים וטאבים
}

// פונקציה לעיבוד קובץ עם מקרואים
void pre_assembler(const char *filename) {
    const char *extension = ".as";
    size_t len = strlen(filename);
    if (len < 3 || strcmp(filename + len - 3, extension) != 0) {
        printf("File %s does not have a .as extension. Skipping.\n", filename);
        return;
    }

    char new_filename[256];
    strncpy(new_filename, filename, len - 3);
    new_filename[len - 3] = '\0';
    strcat(new_filename, ".ad");

    FILE *input_file = fopen(filename, "r");
    FILE *output_file = fopen(new_filename, "w");
    if (!input_file || !output_file) {
        perror("Failed to open files");
        if (input_file) fclose(input_file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    char macro_name[50];
    char macro_content[MAX_LINES_PER_MACRO][MAX_LINE_LENGTH];
    int inside_macro = 0;
    int line_count = 0;

    while (fgets(line, sizeof(line), input_file)) {
        remove_extra_spaces(line);
        line[strcspn(line, "\n")] = '\0';  // הסרת תו סוף שורה

         // בדיקה אם השורה ריקה
        if (is_empty_line(line)) {
            continue; // דילוג על שורות ריקות
        }

        if (strncmp(line, "mcro ", 5) == 0) {
            inside_macro = 1;
            line_count = 0;
            sscanf(line + 5, "%s", macro_name);
        } else if (inside_macro && strncmp(line, "mcroend ",8) == 0) {
            add_macro(macro_name, macro_content, line_count);
            inside_macro = 0;
        } else if (inside_macro) {
            strncpy(macro_content[line_count++], line, MAX_LINE_LENGTH);
        } else {
            Macro *macro = find_macro(line);
            if (macro) {
                for (int i = 0; i < macro->line_count; i++) {
                    fputs(macro->content[i], output_file);
                    fputc('\n', output_file);
                }
            } else {
                fputs(line, output_file);
                fputc('\n', output_file);
            }
        }
    }

    fclose(input_file);
    fclose(output_file);

    printf("File %s processed and saved to %s\n", filename, new_filename);
}

const char *load_file(int argc, char *filename) {
    static char filename_with_extension[256];
     snprintf(filename_with_extension, sizeof(filename_with_extension), "test-files/%s.as", filename);
    FILE *file = fopen(filename_with_extension, "r");
    if (!file) {
        printf("Error: File %s does not exist. Skipping.\n", filename_with_extension);
        return NULL;
    }
    fclose(file);
    return filename_with_extension;
}

// פונקציה שבודקת את מספר השורות בקובץ .ad ויוצרת קובץ .ah עם מספר השורות
void check_the_file(const char *filename_ad) {
    FILE *file = fopen(filename_ad, "r");
    if (!file) {
        printf("Error: Unable to open %s for reading.\n", filename_ad);
        return;
    }

    int line_count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line_count++;
    }
    fclose(file);

    // יצירת שם הקובץ עם סיומת .ah
    char filename_ah[256];
    strncpy(filename_ah, filename_ad, strlen(filename_ad) - 3);
    filename_ah[strlen(filename_ad) - 3] = '\0';
    strcat(filename_ah, ".ah");

    // כתיבת מספר השורות לקובץ .ah
    FILE *file_ah = fopen(filename_ah, "w");
    if (!file_ah) {
        printf("Error: Unable to open %s for writing.\n", filename_ah);
        return;
    }

    fprintf(file_ah, "Number of lines: %d\n", line_count);
    fclose(file_ah);

    printf("File %s created with %d lines.\n", filename_ah, line_count);
}