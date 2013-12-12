#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFSIZE    4096

#define err_sys(info)                                            \
{                                                                \
    printf("%s\n", (info));                                       \
    exit(-1);                                                    \
}

int main()
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write error");
        }
    }

    if (n < 0) {
        err_sys("Read Error");
    }

    return 0;
}
