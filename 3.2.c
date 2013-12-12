#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define  FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

#define err_sys(info)                                            \
{                                                                \
    printf("%s\n", (info));                                       \
    exit(-1);                                                    \
}

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
    int fd;

    if ((fd = open("file.nohole", O_WRONLY)) < 0) {
        printf("Open Error\n");
    }

    if ((fd = creat("file.nohole", FILE_MODE)) < 0) {
        err_sys("Create Error\n");
    }

    if (write(fd, buf1, 10) != 10) {
        err_sys("buf1 write error\n");
    }

    if (lseek(fd, 16384, SEEK_SET) == -1) {
        err_sys("lseek error\n");
    }

    if (write(fd, buf2, 10) != 10) {
        err_sys("buf2 write error\n");
    }

    if (close(fd) < 0) {
        err_sys("Close Error\n");
    }

    return 0;
}
