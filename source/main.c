#include "../headers/utils.h"
#include "../headers/globals.h"
#include "../headers/error.h"

int main(int argc, char *argv[]) {
    if (argc < MIN_PARAM) {
        // printf("Usage: %s <filename (without extension)>\n", argv[0]);
        print_system_error(ERROR_CODE_1);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *as_file = load_file(argc, argv[i]);
        if (as_file != NULL) {
            // יוצרים את הקובץ .ad
            pre_assembler(as_file);

            // בודקים את הקובץ .ad ומייצרים קובץ .ah
            char filename_ad[256];
            snprintf(filename_ad, sizeof(filename_ad), "test-files/%s.ad", argv[i]);
            check_the_file(filename_ad);
        } else {
            printf("in main not found\n");
            printf("File %s.as not found.\n", argv[i]);
        }
    }

    return 0;
}
