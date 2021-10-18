#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *argv[3];

    printf("Before exec function\n");

    argv[0] = "ls";
    argv[1] = "-a";
    argv[2] = NULL;
    if (execv("/bin/ls", argv) == -1) {
        perror("execv");
        exit(1);
    }

    printf("After exec function\n");

    return 0;
}
