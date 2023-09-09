#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char input[1024];
    char *args[1024];
    char *line = NULL;
    char *token;
    size_t len = 0;
    __ssize_t read;
    if (argc == 1)
    {
        while (1)
    {
        printf("wish> ");

        if (fgets(input, 1024, stdin) == NULL) {
            perror("fgets");
            exit(1);
        }

        while (read = getline(&line, len, input) != -1 )
        {
            line = strsep(line, "\n");
            int i = 0;
            token = strtok(line, " ");
            while (token != NULL) {
                args[i] = token;
                i ++;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;
            if (args[0] == "exit") {
                exit(0);
            }
            
        }
        if (read == -1) {
            free(line);
            exit(0);
        }
        
    }
    }
    else if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("wish: cannot open file\n");
            exit(1);
        }
        
    }
    
    
    
    
}