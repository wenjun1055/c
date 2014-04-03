#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[])
{
    int             fdin, fdout;
    void            *src, *dst;
    struct stat     statbuf;

    if (3 != argc) {
        printf("usage: %s <fromfile> <tofile>\n", argv[0]);
        exit(-1);
    }

    if ((fdin = open(argv[1], O_RDONLY)) < 0) {
        printf("can't open %s for reading\n", argv[1]);
        exit(-1);
    }

    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0) {
        printf("can't create %s for writing\n", argv[2]);
        exit(-1);
    }

    if (fstat(fdin, &statbuf) < 0) {
        printf("fstat error\n");
        exit(-1);
    }

    if (lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1) {
        printf("lseek error\n");
        exit(-1);
    }

    if (write(fdout, "", 1) != 1) {
        printf("lseek error\n");
        exit(-1);
    }

    if ((src = mmap(0, statbuf.st_size, PORT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED) {
        printf("mmap error for input\n");
        exit(-1);
    }
    
    if ((dst = mmap(0, statbuf.st_size, PORT_READ | PORT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED) {
        printf("mmap error for output\n");
        exit(-1);
    }

    memcpy(dst, src, statbuf.st_size);

    return 0;
}
