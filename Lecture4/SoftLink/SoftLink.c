#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    symlink("linux.txt", "linux.sym");

    return 0;
}
