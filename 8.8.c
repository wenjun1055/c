#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char    *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void)
{
    pid_t   pid;

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        if (execle("/home/sar/bin/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0) {
            printf("execle error\n");
            exit(-1);
        }
    }

    if (waitpid(pid, NULL, 0) < 0) {
        printf("wait error\n");
        exit(-1);
    }

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0) {
            printf("ececlp error\n");
            exit(-1);
        }
    }

    return 0;
}
