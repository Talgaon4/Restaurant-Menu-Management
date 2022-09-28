#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define MAXSIZE 1024
#define SIZENAME 100

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Bad number of arguments\n");
        exit(1);
    }
    char filename[SIZENAME], buff[MAXSIZE];
    int fd, rbytes;
    memset(buff, 0, MAXSIZE);  //rest the buffer
    sprintf(filename, "%s.txt", argv[1]);
    if ((fd = open(filename, O_RDONLY)) == -1) {
        if (errno == ENOENT)
            fprintf(stderr, "Restaurant not found\n");
        else
            perror("open");
        return (-1);
    }
    if ((rbytes = read(fd, buff, MAXSIZE)) == -1) {
        perror("read\n"); return(-1);
    }
    printf("%s", buff);  //printing the menu
    printf("\n");
    close(fd);
}