#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 6;
char buf[] = "a write to sydout\n";

int main(void)
{
    int     var;
    pid_t   pid;

    var = 88;
    
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != (sizeof(buf) - 1)) {
        printf("write error\n");
        exit(-1);
    }

    printf("before fork\n");

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        glob++;
        var++;
    } else {
        sleep(2);
    }

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
}
