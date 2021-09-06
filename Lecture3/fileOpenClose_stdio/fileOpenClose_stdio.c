#include <stdio.h>
#include <stdlib.h>

int main (void) {
    FILE *fp;
    
    // file open
    if ((fp = fopen("hello.txt", "w")) == NULL) {
        perror("fopen: hello.txt");
        exit(1);
    }

    // file close
    fclose(fp);

    return 0;
}