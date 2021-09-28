#include "sp_common.h"

#define SIZE_OF_MY_INT 3
#define NUM_DATA 10

#define MODE_GEN	0
#define MODE_READ	1

int genBinaryFile(char* _fileName, int _numInts);
int readBinaryFile(char* _inputFileName, char* _outputFileName);

int main(int argc, char** argv) {
	if (argc < 4) {
		printf("Usage(Gen): exec 0 output_file #_of_integers\n");
		printf("Usage(Read): exec 1 input_file output_file\n");
		exit(0);
	}

	switch (atoi(argv[1])) {
	case MODE_GEN:
		genBinaryFile(argv[2], atoi(argv[3]));
		break;
	case MODE_READ:
		readBinaryFile(argv[2], argv[3]);
		break;
	}

	return 0;
}

int readBinaryFile(char* _inputFileName, char* _outputFileName) {

	int rfd = -1;
	IS_SYS_CALL_SUCCESS(rfd = open(_inputFileName, O_RDONLY, 644),"Open input");

	FILE* wfp = fopen(_outputFileName, "w");
	NULL_ERR_CHECK(wfp, "Fail to open output file");

	int numInts = 0;
	IS_SYS_CALL_SUCCESS(numInts = lseek(rfd, 0, SEEK_END)/3, "Move to file end");
	printf("Input file has %d integer values\n", (int)numInts);
	IS_SYS_CALL_SUCCESS(lseek(rfd, 0, SEEK_SET), "Move to file start");

	unsigned int curNum = 0;
	unsigned char buf = 0;
	int readCnt = 0;

	LOOP_I(numInts) {
		curNum = 0;
		LOOP_J(3){
			IS_SYS_CALL_SUCCESS(readCnt = read(rfd, &buf, 1),"Read a byte from input");
			if (!readCnt) break; // EOF

			curNum = curNum << 8;
			curNum += buf;
		}
		printf("%d\n", curNum);
		fprintf(wfp, "%d ", curNum);

		if (!readCnt){
			printf("Read a byte from input\n");
			break;
		}
	}

	EOF_ERR_CHECK(fclose(wfp),"Fail to close output file")
	IS_SYS_CALL_SUCCESS(close(rfd),"Fail to close input file");

	return 0;
}

int genBinaryFile(char* _fileName, int _numInts) {
	const int MAX_MY_INT = pow(2.0, (SIZE_OF_MY_INT*8-1)) - 1;
	unsigned int num = 1;

	char *pByte[SIZE_OF_MY_INT] = { 0 };
	pByte[0] = (char*)&num;
	for (int i = 1; i < SIZE_OF_MY_INT; i++)
		pByte[i] = pByte[i - 1] + 1;

	for (int i = 0; i < SIZE_OF_MY_INT; i++)
		printf("%x ", *pByte[i]);
	printf("\n");

	printf("my int max = %d\n", MAX_MY_INT);

	FILE *fp = fopen(_fileName, "wb");
	FILE *fAnswer = fopen(strcat(_fileName,"_Answer"), "w");

	int count = 0;
	for (int i = 0; i < _numInts; i++) {
		num = rand() % MAX_MY_INT;
		//num = i;
		printf("%d : ", num);
		fprintf(fAnswer, "%d ", num);
		for (int j = SIZE_OF_MY_INT; j > 0; j--) {
			printf("%x ", *pByte[j - 1]);
			fprintf(fp, "%c", *pByte[j - 1]);
		}
		printf("\n");
		count++;
	}

	fclose(fp);
	fclose(fAnswer);
	return count;
}
