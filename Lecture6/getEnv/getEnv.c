#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *val;

    val = getenv("SHELL");
    if (val == NULL)
        printf("SHELL not defined\n");
    else
        printf("SHELL = %s\n", val);

    return 0;
}
