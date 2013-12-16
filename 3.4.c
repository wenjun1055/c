#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main (int argc, char **argv)
{
    int val;

    if (2 != argc) {
        printf("Usage: a.out <descriptor#>\n");
        exit(-1);
    }

    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
        printf("fcntl error for fd %d \n", atoi(*argv+1));
        exit(-1);
    }

    switch (val & O_ACCMODE) {
        case O_RDONLY:
            printf("read only");
            break;

        case O_WRONLY:
            printf("write only");
            break;

        case O_RDWR:
            printf("read write");
            break;

        default:
            printf("unknown access mode");
            exit(-1);
    }

    if (val & O_APPEND) {
        printf(", append");
    }

    if (val & O_NONBLOCK) {
        printf(", nonblock");
    }

#if defined(O_SYNC)
    if (val & O_SYNC) {
        printf(", sync writes");
    }
#endif

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
    if (val & O_FSYNC) {
        printf(", sync writes");
    }
#endif

    putchar('\n');

    return 0;
}
