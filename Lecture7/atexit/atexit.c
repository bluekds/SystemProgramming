#include <stdlib.h>
#include <stdio.h>

void cleanup1(void) {
    printf("Cleanup 1 is called.\n");
}

void cleanup2(void) {
    printf("Cleanup 2 is called.\n");
}

int main(void) {
    atexit(cleanup1);
    atexit(cleanup2);

    exit(0);
}
