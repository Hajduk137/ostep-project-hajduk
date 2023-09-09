#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        exit(0);
    }
    FILE *fp[argc];
    char buffer[1024];
    for (int i = 1; i < argc; i ++){
        fp[i] = fopen(argv[i], "r");

        if (fp[i] == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        while (fgets(buffer, sizeof(buffer), fp[i]) != NULL)
        {
            printf("%s", buffer);
        }

        fclose(fp[i]);
    }
    
    return 0;
}