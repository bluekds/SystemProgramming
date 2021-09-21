#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ON_TIMER	{ startTime = clock();	}
#define OFF_TIMER	{ endTime = clock();	}
#define PRINT_TIMER	\
		{ nProcessExcuteTime = ( (double)(endTime - startTime) ) / CLOCKS_PER_SEC; \
		printf("It takes %f seconds\n", nProcessExcuteTime); }

#define MAX_CHUNK_SIZE 2048

int str2int(char* str);

int main(int argc, char* argv[]) {
	clock_t startTime, endTime;
	double nProcessExcuteTime;

	int rfd, wfd, n;
    char buf[MAX_CHUNK_SIZE];

    if (argc < 4) {
    	printf("Usage: ./exeFile input output chunkSize\n");
    	exit(0);
    }

	int chunkSize = str2int(argv[3]);
    chunkSize
		= (MAX_CHUNK_SIZE < chunkSize ? MAX_CHUNK_SIZE : chunkSize);
    printf("Copy %s to %s (chunk size = %d)\n", argv[1], argv[2], chunkSize);

    rfd = open(argv[1], O_RDONLY);
    if(rfd == -1) {
        perror("Open input file");
        exit(1);
    }

    wfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (wfd == -1) {
        perror("Open output file");
        exit(1);
    }

	ON_TIMER;

    while ((n = read(rfd, buf, chunkSize)) > 0)
        if (write(wfd, buf, n) != n) perror("Write");

    if (n == -1) perror("Read");

	OFF_TIMER;
	PRINT_TIMER;

    close(rfd);
    close(wfd);

    return 0;
}

int str2int(char* str)
{
	int val = str[0] - '0';
	int i = 1;

	while (str[i] != '\0') {
		val *= 10;
		val += str[i] - '0';
		i++;
	}
	return val;
}
