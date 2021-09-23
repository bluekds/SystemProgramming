#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BUF_SIZE 1024
#define ON_TIMER	{ startTime = clock();	}
#define OFF_TIMER	{ endTime = clock();	}
#define PRINT_TIMER	\
		{ nProcessExcuteTime = ( (double)(endTime - startTime) ) / CLOCKS_PER_SEC; \
		printf("It takes %f seconds\n", nProcessExcuteTime); }

int isEqual(const char* _target, const char* _read, int _len);

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Usage: Lab2_2 input.txt target_word\n");
		exit(0);
	}

	clock_t startTime, endTime;
	double nProcessExcuteTime;

	int rfd, n;
	char buf[BUF_SIZE] = { 0 };
	char target[BUF_SIZE] = { 0 };

	int targetLen = 0;
	for (int i = 0; i < BUF_SIZE; i++) {
		target[i] = argv[2][i];
		if (argv[2][i] == '\0')
			break;
		targetLen++;
	}
	printf("The target word is '%s' (size = %d)\n", target, targetLen);

	rfd = open(argv[1], O_RDONLY);
	if (rfd == -1) {
		perror("Open input file");
		exit(1);
	}

	int readState = 0; // 0 : on building, 1: word
	int count = 0;

	char curString[BUF_SIZE] = { 0 };
	int i_read = 0;

	ON_TIMER;
	while ((n = read(rfd, buf, BUF_SIZE)) > 0)
	{
		for (int i = 0; i < n; i++) {
			switch (readState) {
			case 0:	// On building
				if (buf[i] == ' ' || buf[i] == '\n') {
					readState = 1;
					i--;
					break;
				}
				curString[i_read] = buf[i];
				i_read++;
				break;
			case 1: // New word
				curString[i_read] = '\0';
				if (i_read == targetLen)
					count += isEqual(target, curString, targetLen);
				readState = 0;
				i_read = 0;
				break;
			}
		}
	}
	OFF_TIMER;

	if (n == -1) perror("Read");

	printf("# of %s in the text file is %d\n", target, count);
	PRINT_TIMER;

	close(rfd);
}

int isEqual(const char* _target, const char* _read, int _len)
{
	if (_target == NULL || _read == NULL)
		return -1;		// error

	printf("Compare %s : %s", _target, _read);
	for (int i = 0; i < _len; i++) {
		if (_target[i] != _read[i]) {
			printf("\n");
			return 0;	// false
		}
	}
	printf(" - Matched!\n");
	return 1;			// true
}