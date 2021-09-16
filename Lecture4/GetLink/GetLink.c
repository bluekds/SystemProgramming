#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define PRINT_ERR_EXIT(_msg) {perror(_msg); exit(1);}

int main(void) {
    char buf[BUFSIZ];
    int n;

    n = readlink("linux.sym", buf, BUFSIZ);
    if (n == -1) PRINT_ERR_EXIT("readlink");

    buf[n] = '\0';
    printf("linux.sym : READLINK = %s\n", buf);

    realpath("linux.sym", buf);
    printf("linux.sym : REALPATH = %s\n", buf);

    return 0;
}
