#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

#define SIZE 100

int getOrderNum(char* rest_name) {
	char path[SIZE];
	int cnt = 0;
	DIR* dir;
	struct dirent* dr;
	memset(path, 0, SIZE);  //rest the path string
	snprintf(path, SIZE, "Order_%s", rest_name);
	if ((dir = opendir(path)) == NULL) {
		if (errno == ENOENT)
			fprintf(stderr, "Restaurant not found\n");
		else
			perror("open");
		return (-1);
	}

	while ((dr = readdir(dir)) != NULL)  //read and count how many files in the dir
		cnt++;

	closedir(dir);
	printf("%d Orders\n", cnt - 2);  //return the count value -2 because we opened and closed the dir also
	return 0;
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Bad number of arguments\n");
		exit(1);
	}
	getOrderNum(argv[1]);
	return 0;
}