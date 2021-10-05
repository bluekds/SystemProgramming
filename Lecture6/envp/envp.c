#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    char **env;

    env = envp;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}
