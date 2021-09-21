#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//#include <math.h>

#define MIN_ASCII 32 // '\n'
#define MAX_JUMP MIN_ASCII
#define BUF_SIZE 1024

// Decryption mode
#define DECRYPT_MODE_LSEEK 	0
#define DECRYPT_MODE_BUFFER 1
#define DECRYPT_MODE DECRYPT_MODE_LSEEK

// Macro Func.
clock_t startTime, endTime;
double nProcessExcuteTime;
#define ON_TIMER	{ startTime = clock();	}
#define OFF_TIMER	{ endTime = clock();	}
#define PRINT_TIMER	\
		{ nProcessExcuteTime = ( (double)(endTime - startTime) ) / CLOCKS_PER_SEC; \
		printf("It takes %f seconds\n", nProcessExcuteTime); }


// Func. declarations
#define ENCRYPT	0
#define DECRYPT 1

void writeChar(int _wfd, const char _c);
void writeGarbage(int _wfd, int _len);
int putJump();

int Encrypt (const char* _msg, const char* _output);
int EncryptFile (const char* _input, const char* _output);
int Decrypt (const char* _inputFile, const char* _outputFile);

#define P_MODE argv[1]
#define P_INPUT argv[2]
#define P_OUTPUT argv[3]
#define P_LEVEL argv[4]

// Main body
int main(int argc, char* argv[])
{
	if (argc < 4){
		//printf("Usage: Lab2_3.out 0(=encrypt) input output encryptLv(1~10)\n");
		printf("Usage: ./exeFile 0(=encrypt) input output\n");
		printf("Usage: ./exeFile 1(=decrypt) input output\n");
		exit(0);
	}

	ON_TIMER;
	switch (atoi(P_MODE))
	{
	case ENCRYPT:
		printf("Encryption start : %s\n", P_INPUT);
		//Encrypt(P_INPUT, P_OUTPUT, atoi(P_LEVEL));
		EncryptFile(P_INPUT, P_OUTPUT);
		break;

	case DECRYPT:
		Decrypt(P_INPUT, P_OUTPUT);
		break;
	}
	OFF_TIMER;

	PRINT_TIMER;

	return 0;
}

// Func. definitions
int Encrypt (const char* _msg, const char* _output)
{
	int wfd;

	wfd = open(_output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (wfd == -1) {
        perror("Open output file");
        exit(1);
    }

    srand(time(NULL));

    int i = 0;
    int ratio = 100 ; // pow(100,_level);

    while(_msg[i] != '\0') {
    	if (rand()%ratio == 0) {	// Put messages
    		writeChar(wfd, _msg[i]);
    		i++;
    	} else {
    		putJump(wfd);
    	}
    }

	return 0 ;
}

int EncryptFile (const char* _input, const char* _output)
{
	int n = 0;
	int rfd, wfd;

    srand(time(NULL));

    rfd = open(_input, O_RDONLY);
    if(rfd == -1) {
        perror("Open input file");
        exit(1);
    }

	wfd = open(_output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (wfd == -1) {
        perror("Open output file");
        exit(1);
    }


    int ratio = 100 ; //pow(100,_level);

    char buf[BUF_SIZE] = {0} ;
    while ((n = read(rfd, buf, BUF_SIZE)) > 0)
    {
    	for (int i = 0 ; i < n ; i++){
			if (rand()%ratio == 0) {	// Put messages
				if (buf[i] < MIN_ASCII )
					continue;
				writeChar(wfd, buf[i]);
			} else {
				putJump(wfd);
				i--;
			}
    	}
    }

	return 0 ;
}

int Decrypt (const char* _inputFile, const char* _outputFile)
{
	int rfd, wfd;
	int n = 0;
	char buf[BUF_SIZE] = {0} ;

    rfd = open(_inputFile, O_RDONLY);
    if(rfd == -1) {
        perror("Open input file");
        exit(1);
    }

	wfd = open(_outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (wfd == -1) {
        perror("Open output file");
        exit(1);
    }

#if DECRYPT_MODE == DECRYPT_MODE_LSEEK
    // lseek version
    char r = 0;
    while (read(rfd, &r, 1) > 0)
    {
    	if ( MIN_ASCII <= r && r < 128 ){
			writeChar(wfd, r);
			printf("%c", r);
    	} else {
    		if(lseek(rfd, r, SEEK_CUR) == -1)
    			break ;
    	}
    }
#elif DECRYPT_MODE == DECRYPT_MODE_BUFFER
    // Buffered version
    int nJump = 0;
    while ((n = read(rfd, buf, BUF_SIZE)) > 0)
    {
    	for (int i = 0 ; i < n ; i++) {

    		if (nJump > 0) {
    			nJump--;
    			continue;
    		}

    		if ( MIN_ASCII <= buf[i] && buf[i] < 128){	// GO
    			nJump = 0;
    			writeChar(wfd, buf[i]);
    			printf("%c", buf[i]);
    		} else {							// JUMP
    			nJump = buf[i];
    		}
    	}
    }
#else
	printf("Not defined decryption mode\n");
	exit(-1);
#endif

    printf("\n");
	return 0;
}

// Sub-routines
int putJump(int _wfd)
{
	char jump = rand()%MAX_JUMP;
	jump = ( jump > 0 ? jump : 1);

	writeChar(_wfd, jump);
	writeGarbage(_wfd, jump);

	return jump;
}


void writeChar(int _wfd, const char _c)
{
	write(_wfd, &_c, 1);
}

void writeGarbage(int _wfd, int _len)
{
	for (int i = 0 ; i < _len ; i++)
		writeChar(_wfd, rand()%90 + MIN_ASCII);
}
