#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
int main(void) {
    struct stat buf;
    int kind;

    stat("linux.txt", &buf);

    printf("Mode = %o (Hexa: %x)\n"
	    , (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

    kind = buf.st_mode & S_IFMT; // buf.st_mode (AND) (1111 000 000 000)
    printf("Kind = %x\n", kind);

    switch (kind) {
        case S_IFIFO:
            printf("linux.txt : FIFO\n"); break;
        case S_IFDIR:
            printf("linux.txt : Directory\n"); break;
        case S_IFREG:
            printf("linux.txt : Regular File\n"); break;
    }

    return 0;
}
