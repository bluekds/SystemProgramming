#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int pd, n;
    char inmsg[80];

    printf("Client =====\n");
    if ((pd = open("./pipeFile", O_RDONLY)) == -1) {
        perror("open"); exit(1);
    }

    write(1, "From Server :", 13);
    while ((n=read(pd, inmsg, 80)) > 0)
        write(1, inmsg, n);

    if (n == -1) {
        perror("read");
        exit(1);
    }

    write(1, "\n", 1);
    close(pd);

    return 0;
}
