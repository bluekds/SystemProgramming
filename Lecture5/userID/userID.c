#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    uid_t uid, euid;

    uid = getuid();
    euid = geteuid();
    printf("[Init] UID=%d, EUID=%d\n", (int)uid, (int)euid);

    seteuid(getuid());
    int cur_euid = (int)geteuid();
    printf("[seteuid(uid)] UID=%d, EUID=%d\n", (int)uid, (int)cur_euid);

    seteuid(euid);
    cur_euid = (int)geteuid();
    printf("[seteuid(euid)]UID=%d, EUID=%d\n", (int)uid, (int)cur_euid);

    return 0;
}
