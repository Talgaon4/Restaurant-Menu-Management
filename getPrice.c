#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define MAXSIZE 1024
#define SIZENAME 100
int main(int argc, char* argv[]) {
    char* token, * findDish, dish_name[SIZENAME], filename[SIZENAME], * price, buff[MAXSIZE];
    int fd, rbytes, size, i;
    memset(buff, 0, MAXSIZE);//rest the buffer
    if (argc < 3) { //check if number of arguments is at least 3
        printf("Bad number of arguments\n");
        exit(1);
    }
    strcpy(dish_name, argv[2]);
    for (i = 3; i < argc; i++) { //if there are more than 3 arg
        strcat(dish_name, " ");
        strcat(dish_name, argv[i]);
    }
    sprintf(filename, "%s.txt", argv[1]);
    if ((fd = open(filename, O_RDONLY)) == -1) {
        if (errno == ENOENT)
            fprintf(stderr, "Restaurant not found\n");
        else
            perror("open");
        return (-1);
    }
    if ((rbytes = read(fd, buff, size)) == -1) {
        perror("read\n"); return(-1);
    }
    buff[rbytes] = '\0';
    findDish = strstr(buff, dish_name);
    if (findDish) {  //if the dish has founded then get the price
        findDish = strtok(findDish, "\n");
        findDish = strrchr(findDish, '.');
        price = strtok(findDish, "N");

        printf("%s NIS\n", ++price);
    }
    else
        printf("Dish not found\n");
    close(fd);
    return 0;
}