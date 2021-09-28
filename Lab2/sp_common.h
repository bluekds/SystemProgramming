#ifndef _COMMON_H_
#define _COMMON_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Macro functions
#define IS_SYS_CALL_SUCCESS(_fd,_msg) \
	if ((_fd) == -1) {	\
		perror(_msg);	\
		exit(1);		\
	}

#define NULL_ERR_CHECK(_op,_msg) \
	if ((_op) == NULL) {	\
		perror(_msg);	\
		exit(1);		\
	}

#define EOF_ERR_CHECK(_op,_msg) \
	if ((_op) == EOF) {	\
		perror(_msg);	\
		exit(1);		\
	}

// Print
#define PRINT_LINE_INFO printf("%s, line %d", __FILE__, __LINE__)
#define PRINT_ERROR_MSG(_msg) {PRINT_LINE_INFO; printf(" at "); printf(_msg);}

// Single loops
#define LOOP_I(a) for(int i=0; i<a; i++)
#define LOOP_J(a) for(int j=0; j<a; j++)
#define LOOP_K(a) for(int k=0; k<a; k++)
#define LOOP_INDEX(index, end) for (int index = 0 ; index < end ; index++)
#define LOOP_INDEX_START_END(index, start, end) for (int index = start ; index < end ; index++)

#endif ///// end of files
