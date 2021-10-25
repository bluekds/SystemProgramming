#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

extern int errno;

int main(void)
{
    int targetPID = 0;

    while (1)
    {
        printf("Enter PID to kill : ");
        scanf("%d", &targetPID);
        if (kill(targetPID, SIGKILL) == -1) {
            switch (errno)
            {
            case EPERM:
                printf("Not enough permission!\n");
                break;
            case ESRCH:
                printf("Cannot find the process %d\n", targetPID);
                break;
            }
        } else {
            printf("Bang! -> %d\n", targetPID);
            }
        }
    }