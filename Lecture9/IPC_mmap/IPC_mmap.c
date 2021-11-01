#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHECK_MMAP_SUCCESS(_addr) \
    if (_addr == MAP_FAILED)      \
    {                             \
        perror("mmap");           \
        exit(1);                  \
    }

int main(int argc, char *argv[])
{
    int fd;
    caddr_t addr;
    char fileName[255] = "input.dat";

    if (argc > 1)
        strcpy(fileName, argv[1]);

    if ((fd = open(fileName, O_RDWR)) == -1)
    {
        perror("open");
        exit(1);
    }

    int pageSize = getpagesize();

    addr = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    CHECK_MMAP_SUCCESS(addr);
    close(fd);

    int pid = 0;
    switch (pid = fork())
    {
    case -1: /* fork failed */
        perror("fork");
        exit(1);
        break;
    case 0: /* child process */
        printf("1. Child Process : addr=%s", addr);
        sleep(1);
        addr[0] = 'x';
        printf("2. Child Process : addr=%s", addr);
        sleep(2);
        printf("3. Child Process : addr=%s", addr);
        break;
    default: /* parent process */
        printf("1. Parent process : addr=%s", addr);
        sleep(2);
        printf("2. Parent process : addr=%s", addr);
        addr[1] = 'y';
        printf("3. Parent process : addr=%s", addr);
        break;
    }

    return 0;
}
