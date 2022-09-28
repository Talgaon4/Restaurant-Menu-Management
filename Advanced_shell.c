#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAXSIZE 1024
#define SIZE 100

int checkFunc(char* input) {
    if (!strcmp(input, "CreateMenu"))
        return 1;
    else if (!strcmp(input, "getMenu"))
        return 1;
    else if (!strcmp(input, "MakeOrder"))
        return 1;
    else if (!strcmp(input, "getPrice"))
        return 1;
    else if (!strcmp(input, "getOrderNum"))
        return 1;
    return 0;  //not an advanced shell function
}
int main() {
    char input[MAXSIZE];
    char* argv[4];
    char path[SIZE];
    int i;
    while (1) {
        for (i = 0; i < 4; i++)
            argv[i] = NULL;  //reset argv[]
        printf("AdvShell>");

        fgets(input, MAXSIZE, stdin);
        while (strcmp(input, "\n") == 0) {  //check if the user enter an empty line
            printf("AdvShell>");
            fgets(input, MAXSIZE, stdin);
        }
        input[strlen(input) - 1] = '\0';  //close the string

        if (strcmp(input, "exit") == 0) {
            printf("GoodBye!\n");
            return 0;
        }
        argv[0] = strtok(input, " ");
        if (checkFunc(argv[0]) == 0)
            strcpy(path, "/bin/");
        else
            strcpy(path, "/home/braude/");

        //split the arguments for exec
        for (i = 1; i < 4; i++)
            argv[i] = strtok(NULL, " "); //get arguments

        strcat(path, argv[0]);

        if (fork() != 0) {  //only Parent does the next line 
            wait();  //the parent will wait for the child to end
        }
        else {  //Only child does the next line
            execl(path, argv[0], argv[1], argv[2], argv[3], NULL);  //execute command
            if (errno == ENOENT) {
                fprintf(stderr, "Not Supported\n");
                return 0;
            }
            perror("execl");
            return (-1);
        }
    }
}