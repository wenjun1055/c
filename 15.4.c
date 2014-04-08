#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PAGER "${PAGER:-more}"
#define MAXLINE 1024

int main(int argc, char *argv[])
{
    char    line[MAXLINE];
    FILE    *fpin, *fpout;

    if (2 != argc) {
        printf("usage: a.out <pathname>");
        exit(-1);
    }

    if ((fpin = fopen(argv[1], "r")) == NULL) {
        printf("can't open %s\n", argv[1]);
        exit(-1);
    }

    if ((fpout = fopen(PAGER, "w")) == NULL) {
        printf("popen error\n");
        exit(-1);
    }

    while (fgets(line, MAXLINE, fpin) != NULL) {
        if (fputs(line, fpout) == EOF) {
            printf("fputs error to pipe\n");
            exit(-1);
        }
    }

    if (ferror(fpin)) {
        printf("fgets error\n");
        exit(-1);
    }

    if (pclose(fpout) == -1) {
        printf("pclose error");
        exit(-1);
    }

    return 0;
}
