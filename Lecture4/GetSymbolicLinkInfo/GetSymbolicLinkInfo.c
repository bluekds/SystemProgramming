#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#define PRINT_CNT_INODE {\
printf("linux.txt : Link Count = %d\n", (int)buf.st_nlink);\
printf("linux.txt : Inode = %d\n", (int)buf.st_ino); }

int main(void) {
    struct stat buf;

    printf("1. stat : linux.txt ---\n");
    stat("linux.txt", &buf);
    PRINT_CNT_INODE;

    printf("2. stat : linux.sym ---\n");
    stat("linux.sym", &buf);
    PRINT_CNT_INODE;

    printf("3. lstat : linux.sym ---\n");
    lstat("linux.sym", &buf);
    PRINT_CNT_INODE;

    return 0;
}
