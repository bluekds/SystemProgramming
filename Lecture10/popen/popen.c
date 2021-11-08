#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    char buf[256];

    fp = popen("date", "r");
    if (fp == NULL) {
        fprintf(stderr, "popen failed\n");
        exit(1);
    }

    if (fgets(buf, sizeof(buf), fp) == NULL) {
        fprintf(stderr, "No data from pipe!\n");
        exit(1);
    }

    printf("line : %s\n", buf);
    pclose(fp);

    return 0;
}
