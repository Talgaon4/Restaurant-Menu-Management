#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

#define SIZE 100
#define MAX_SIZE 1024

int MakeOrder(char* rest_name, char* order_name) {
    char filename[SIZE], * findDish, input[SIZE], * token, dir[SIZE];
    char* dish_num, * dish_price, choice[SIZE], toprint[SIZE], curr[SIZE], buff[MAX_SIZE], dish_name[SIZE], add[SIZE], toprint_time[SIZE];
    int fd, fc, rbytes, total_price = 0, wbytes;
    srand(time(0));
    time_t Time;
    struct tm* info;
    time(&Time);
    info = localtime(&Time); //get the current date
    memset(toprint, 0, SIZE);
    snprintf(toprint, SIZE, "%s Order\n\n", rest_name);
    sprintf(filename, "%s.txt", rest_name);
    //open the currect resturant file
    if ((fd = open(filename, O_RDONLY)) == -1) {
        if (errno == ENOENT)
            fprintf(stderr, "Restaurant not found\n");
        else
            perror("open");
        return (-1);
    }
    printf("Insert your order (Finish to finish):\n");
    //get dishes order from user untill inset Finish
    while (1) {
        memset(buff, 0, MAX_SIZE);
        if ((rbytes = read(fd, buff, MAX_SIZE)) == -1) {
            perror("read 1\n"); return(-1);
        }
        lseek(fd, 0, SEEK_SET); //reset the file pointer to the start of the file
        rewind(stdin);

        fgets(input, SIZE, stdin);
        if (strcmp(input, "Finish\n") == 0)
            break; //get out from the loop if insert "Finish"

        //get the name and the num of orders of a dish
        dish_num = strrchr(input, ' ');
        memset(dish_name, 0, SIZE);
        strncpy(dish_name, input, strlen(input) - strlen(dish_num));
        dish_num[strlen(dish_num) - 1] = '\0';
        findDish = strstr(buff, dish_name);
        //search the dish at the menu and add the dish price(*num of orders) to total price
        if (findDish) {
            strcat(toprint, input);
            strcat(toprint, "\n");
            token = strtok(findDish, "\n");
            token = strrchr(token, '.');
            dish_price = strtok(token, "N");
            dish_price++;
            total_price += (atoi(dish_price) * atoi(dish_num));
        }
        else {
            printf("Dish Not Found!\n");
        }
    }
    printf("Total Price: %d NIS (Confirm to approve/else cancle)\n", total_price);
    rewind(stdin);
    while (1) {
        fgets(choice, SIZE, stdin);
        if (strcmp(choice, "cancle\n") == 0) {
            printf("Order is cancled!");
            return 0;
        }
        else if (strcmp(choice, "Confirm\n") == 0) {
            memset(add, 0, SIZE);
            sprintf(add, "\nTotal price: %d", total_price);
            strcat(toprint, add);
            strcat(toprint, "NIS\n");
            //current time printing
            snprintf(toprint_time, SIZE, "\n%02d/%02d/%04d", info->tm_mday, info->tm_mon + 1, info->tm_year + 1900);
            strcat(toprint, toprint_time);
            strcat(order_name, ".txt");
            sprintf(dir, "Order_%s", rest_name);
            mkdir(dir, 0777);  //open a dir for the resturant
            getcwd(curr, SIZE);  //save the curr location
            chdir(dir);  //move into the new dir
            if ((fc = open(order_name, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1) {
                perror("Open Failed.");
                exit(1);
            }
            if ((wbytes = write(fc, toprint, strlen(toprint))) == -1) {
                perror("Write Failed."); close(fc); exit(1);
            }
            printf("Order created!\n");
            chmod(order_name, 0444);  //change premmisions to read only
            chdir(curr);  //return to home dir
            return 0;
        }
        else {
            printf("Invalid choice, please try again!\n");
        }
    }
}

int main(int argc, char* argv[]) {
    char name1[SIZE], name2[SIZE];
    if (argc != 3) {
        printf("Bad number of arguments\n");
        exit(1);
    }
    strcpy(name1, argv[1]);
    strcpy(name2, argv[2]);
    MakeOrder(name1, name2);
    return 0;
}