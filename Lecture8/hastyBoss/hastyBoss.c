#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

#define COFFEE 0
#define CAKE 1
int totalOrder[2];

void salesCheck(int _sig)
{
    printf("\n[Total orders of today!]\n");
    printf("Coffee : %d, Cake : %d\n", totalOrder[COFFEE], totalOrder[CAKE]);
    alarm(5);
}

int main(void)
{
    int order = 0;
    memset(totalOrder, 0, sizeof(int) * 2);
    signal(SIGALRM, salesCheck);
    signal(SIGTERM, salesCheck);

    alarm(5);
    while (1)
    {
        printf("Enter order (0 : coffee, 1: cake) : ");
        scanf("%d", &order);
        if (order == 0 || order == 1)
            totalOrder[order]++;
    }
}
