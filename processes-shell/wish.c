#include <asm-generic/errno-base.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char *argv[]) {


    char *path[102] = {"/bin", NULL};
    char *line = NULL;
    char *cmd;
    char error_message[30] = "An error has occurred\n";
    size_t len = 0;
    __ssize_t read;
    if (argc == 1)//interactive mode
    {
        printf("wish> ");


        while ((read = getline(&line, &len, stdin) )!= -1 )
        {

            line[strcspn(line, "\n")] = 0;
            int n = 0;
            cmd = strtok(line, "&");
            while (cmd != NULL) {
                char *args[102];
                int i = 0;
                char *token = strtok(cmd, " ");
                while (token != NULL) {
                    args[i] = token;
                    i ++;
                    token = strtok(NULL, " ");
                }
                args[i] = NULL;

                if (strcmp(args[0], "exit") == 0) {
                    free(line);
                    exit(0);
                }
                else if (strcmp(args[0], "cd") == 0) {
                    if (i == 2) {

                        if (chdir(args[1]) == -1) {

                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                    }
                    else {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                    }
                    cmd = strtok(NULL, "&");
                    continue;
                }
                else if (strcmp(args[0], "path") == 0) {
                    for (int j = 0; j < i - 1; j ++) {
                        path[j] = args[j + 1];
                    }
                    path[i - 1] = NULL;
                    cmd = strtok(NULL, "&");
                    continue;
                }

                int childprocess = fork();
                n += 1;
                if (childprocess < 0) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    exit(1);
                }
                else if (childprocess == 0) {


                    int fd = -1;  // 文件描述符
                    // 检查重定向
                    for (int j = 0; j < i; j++) {
                        if (strcmp(args[j], ">") == 0) {
                            if (args[j + 1] != NULL) {
                                fd = open(args[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                                if (fd == -1) {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                    exit(1);
                                }
                                dup2(fd, STDOUT_FILENO);
                                close(fd);
                                args[j] = NULL;  // 结束参数列表
                                break;
                            }
                        }
                    }



                    char cmdpath[102];
                    int j = 0;
                    while (path[j] != NULL) {
                        snprintf(cmdpath, sizeof(cmdpath), "%s/%s", path[j], args[0]);
                        if (access(cmdpath, X_OK) == 0) {
                            execv(cmdpath, args);
                            write(STDERR_FILENO, error_message, strlen(error_message));
                            exit(1);
                        }
                        j ++;
                    }
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    exit(1);

                }



                cmd = strtok(NULL, "&");


            }
                for (int g = 0; g < n; g ++) {
                    wait(NULL);
                }


                printf("wish> ");

        }
        free(line);





        
    }

    else if (argc == 2)//batch mode
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            write(STDERR_FILENO, error_message, strlen(error_message));
            exit(1);
        }

        while ((read = getline(&line, &len, file) )!= -1 )
        {

            line[strcspn(line, "\n")] = 0;
            int n = 0;
            cmd = strtok(line, "&");
            while (cmd != NULL) {
                char *args[102];
                int i = 0;
                char *token = strtok(cmd, " ");
                while (token != NULL) {
                    args[i] = token;
                    i ++;
                    token = strtok(NULL, " ");
                }
                args[i] = NULL;

                if (strcmp(args[0], "exit") == 0) {
                    if (i != 1) {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                    }
                    free(line);
                    exit(0);
                }
                else if (strcmp(args[0], "cd") == 0) {
                    if (i == 2) {

                        if (chdir(args[1]) == -1) {

                            write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                    }
                    else {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                    }
                    cmd = strtok(NULL, "&");
                    continue;
                }
                else if (strcmp(args[0], "path") == 0) {
                    for (int j = 0; j < i - 1; j ++) {
                        path[j] = args[j + 1];
                    }
                    path[i - 1] = NULL;
                    cmd = strtok(NULL, "&");
                    continue;
                }

                int childprocess = fork();
                n += 1;
                if (childprocess < 0) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    exit(1);
                }
                else if (childprocess == 0) {


                    int fd = -1;
                    int found = 0;

                    for (int j = 0; j < i; j++) {// 检查重定向
                        if (strcmp(args[j], ">") == 0) {
                            if (args[j + 1] != NULL) {
                                fd = open(args[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                                if (fd == -1) {
                                    write(STDERR_FILENO, error_message, strlen(error_message));
                                    exit(1);
                                }
                                dup2(fd, STDOUT_FILENO);
                                close(fd);
                                args[j] = NULL;  // 结束参数列表
                                break;
                            }
                        }
                    }



                    char cmdpath[102];
                    int j = 0;
                    while (path[j] != NULL) {
                        snprintf(cmdpath, sizeof(cmdpath), "%s/%s", path[j], args[0]);
                        if (access(cmdpath, X_OK) == 0) {
                            execv(cmdpath, args);
                            write(STDERR_FILENO, error_message, strlen(error_message));
                            exit(1);
                        }
                        j ++;
                    }

                    int len = strlen(args[0]);
                    if (len > 3 && strcmp(args[0] + len - 3, ".sh") == 0) {
                        while (path[j] != NULL) {
                            snprintf(cmdpath, sizeof(cmdpath), "%s/%s", path[j], args[0]);
                            if (access(cmdpath, X_OK) == 0) {  // 确保.sh文件是可执行的
                                char *new_args[103] = {"/bin/bash", cmdpath};
                                for (int k = 1; k <= i; k++) {
                                    new_args[k + 1] = args[k];
                                }
                                execv("/bin/sh", new_args);
                                found = 1;
                                break;
                            }
                            j++;
                        }
                    }
                    else {
                        while (path[j] != NULL) {
                            snprintf(cmdpath, sizeof(cmdpath), "%s/%s", path[j], args[0]);
                            if (access(cmdpath, X_OK) == 0) {
                                execv(cmdpath, args);
                                found = 1;
                                break;
                            }
                            j++;
                        }
                    }
                    if (!found) {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                        exit(1);
                    }

                }



                cmd = strtok(NULL, "&");


            }
                for (int g = 0; g < n; g ++) {
                    wait(NULL);
                }
        
    }
    
    
    
    
    }
    else {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }

    return 0;
}
