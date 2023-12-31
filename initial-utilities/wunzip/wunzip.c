#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
     if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i < argc; i ++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        int count;
        char ch;
        while (fread(&count, sizeof(int), 1, file) == 1) {
            ch = fgetc(file);
            for (int j = 0; j < count; j ++)
            {
                fputc(ch, stdout);
            }
            
        }
        fclose(file);
    }
    return 0;
}