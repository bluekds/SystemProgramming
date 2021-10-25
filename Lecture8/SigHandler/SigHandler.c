#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int signo)
{
    printf("Caught SIGINT!\n");
    psignal(signo, "Received signal");
}

int main(void)
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    for (;;)
        pause(); // pause(2) : waiting a signal (any signal)
    return 0;
}
