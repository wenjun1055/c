#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int     glob = 6;

int main(void)
{
    int     var;
    pid_t   pid;

    var = 88;
    
    printf("before fork\n");
    if ((pid = vfork()) < 0) {
        printf("vfork error\n");
        exit(-1);
    } else if (0 == pid) {
        glob++;
        var++;
     //   exit(0);
        _exit(0);
    }

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}
