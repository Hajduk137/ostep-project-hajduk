#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    char curr_char, prev_char;
    int count = 0;
    for (int i = 1; i < argc; i ++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        
        while ((curr_char = fgetc(file)) != EOF) {
            if (count == 0) {
                prev_char = curr_char;
                count = 1;
            } else if (curr_char == prev_char) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(prev_char, stdout);
                prev_char = curr_char;
                count = 1;
            }
        }
        
        fclose(file);

    }
    if (count > 0) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(prev_char, stdout);
    }
    return 0;
}