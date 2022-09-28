#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define SIZE 100
#define MAXSIZE 1024

void createMenu(char* rest_name, int num_dishes) {
    int i, j, k, wbytes, fd;
    char input[SIZE], dish_type[SIZE], *price, *token, dishtype_ch = 'a', dish_name[SIZE];
    char filename[SIZE], toprint[MAXSIZE];
    int max_len = sizeof(toprint);

    sprintf(filename, "%s.txt", rest_name);
    if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1) {
        perror("Open Failed.");
        exit(1);
    }
    sprintf(toprint, "%s Menu\n", rest_name);
    if ((wbytes = write(fd, toprint, strlen(toprint))) == -1) {
        perror("Write Failed."); close(fd); exit(1);
    }
    //loop in size of number dishes type
    for (i = 0; i < num_dishes; i++) {
        printf("Insert Type Dish %c:\n", dishtype_ch);
        rewind(stdin);
        fgets(dish_type, SIZE, stdin);  // get dish type
        dish_type[strlen(dish_type) - 1] = '\0';
        snprintf(toprint, max_len, "\n%c. %s\n", dishtype_ch++, dish_type);
        if ((wbytes = write(fd, toprint, strlen(toprint))) == -1) {
            perror("Write Failed."); close(fd); exit(1);
        }
        j = 1;
        //get dishes from the user untill he insert "stop"
        while (1) {
            memset(toprint, 0, MAXSIZE);
            printf("Insert dish name %d: \n", j++);
            rewind(stdin);
            fgets(input, SIZE, stdin);  //get dish type
            input[strlen(input) - 1] = '\0';
            if (strcmp(input, "Stop") == 0) {
                break;
            }
            price = strrchr(input, ' ');
            price++;
            token = strtok(input, " ");
            while (strcmp(token, price) != 0) {
                strcat(toprint, token);
                strcat(toprint, " ");
                token = strtok(NULL, " ");
            }
            sprintf(dish_name, "%s", toprint);  //save the dishname
            //loop for writing '....' between dish name and dish price
            for (k = 0;k < (30 - strlen(dish_name) - strlen(price)); k++) {
                strcat(toprint, ".");
            }
            strcat(toprint, price);
            strcat(toprint, "NIS\n");
            if ((wbytes = write(fd, toprint, strlen(toprint))) == -1) {
                perror("Write Failed."); close(fd); exit(1);
            }
        }
    }
    sprintf(toprint, "Bon Appetit");
    if ((wbytes = write(fd, toprint, strlen(toprint))) == -1) {
        perror("Write Failed."); close(fd); exit(1);
    }
    printf("Successfully created\n");
}

int main(int argc, char* argv[]) {
    char name[SIZE];
    int num = atoi(argv[2]);
    if (argc != 3) {
        printf("Bad number of arguments\n");
        exit(1);
    }
    strcpy(name, argv[1]);
    createMenu(name, num);
}