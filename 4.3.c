#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main()
{
    umask(0);
    if (creat("foo", RWRWRW) < 0) {
        printf("creat error for foo\n");
    }

    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if (creat("bar", RWRWRW) < 0) {
        printf("creat error for bar\n");
    }

    return 0;
}
