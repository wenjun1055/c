#include <stdio.h>
#include <stdlib.h>

static void charatatime(char *str)
{
    char    *ptr;
    int     c;

    setbuf(stdout, NULL);

    for (ptr = str; (c = *ptr++) != 0;) {
        putc(c, stdout);
    }

}

int main(void)
{
    pid_t   pid;

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
    }

    return 0;
}
