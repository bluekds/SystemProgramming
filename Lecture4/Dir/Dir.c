#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PRINT_ERR_EXIT(_msg) {perror(_msg); exit(1);}

int main(void) {
    if (mkdir("system", 0755) == -1)
        PRINT_ERR_EXIT("system");

    if (mkdir("programming", 0755) == -1)
        PRINT_ERR_EXIT("programming");

    if (rename("system", "systemProgramming") == -1)
        PRINT_ERR_EXIT("systemProgramming");

    if (rmdir("programming") == -1)
        PRINT_ERR_EXIT("programming");

    return 0;
}
