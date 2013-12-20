#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char buf[1024];
    int bufsize;

    if (3 != argc) {
        printf("Arguments num error!\n");
        exit(-1);
    }

    if (symlink(*(argv + 1), *(argv + 2)) < 0) {
        printf("Create symlink error!\n");
        exit(-1);
    } else {
        printf("Create symlink Success!\n");
    }

    if (bufsize = readlink(*(argv + 2), buf, 1024) < 0) {
        printf("%s : Readlink error!\n", *(argv + 2));
        exit(-1);
    } else {
        printf("%s : Readlink Success! BufSize : %d\n", *(argv + 2), bufsize);
    }

    return 0;
}
