#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    FILE *fp[argc];
    char *line = NULL;
    size_t len = 0;
    char *term;
    term = argv[1];

    if (argc == 1) 
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    else if (argc == 2) {
        while (getline(&line, &len, stdin) != -1)
        {
            if (strstr(line, term) != NULL) {
                printf("%s", line);
            }
        }
        free(line);
    }
    else {
        for (int i = 2; i < argc; i ++)
    {
        fp[i] = fopen(argv[i], "r");
        if (fp[i] == NULL) 
        {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        while (getline(&line, &len, fp[i]) != -1)
        {
            if (strstr(line, term) != NULL) {
                printf("%s", line);
            }
        }
        free(line);
        fclose(fp[i]);
    }
    
    }
    return 0;
    
}