#include <sys/types.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    time_t t;
    struct tms mytms;
    clock_t t1, t2;

    if ((t1 = times(&mytms)) == -1)
    {
        perror("times 1");
        exit(1);
    }

    sleep(5);

    for (int i = 0; i < 999999; i++)
        time(&t);

    if ((t2 = times(&mytms)) == -1)
    {
        perror("times 2");
        exit(1);
    }

    printf("Real time : %.1f sec\n", (double)(t2 - t1) / sysconf(_SC_CLK_TCK));
    printf("User time : %.1f sec\n", (double)mytms.tms_utime / sysconf(_SC_CLK_TCK));
    printf("System time : %.1f sec\n", (double)mytms.tms_stime / sysconf(_SC_CLK_TCK));
    return 0;
}