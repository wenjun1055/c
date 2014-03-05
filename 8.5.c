#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;

    if (0 > (pid = fork())) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        if (0 > (pid = fork())) {
            printf("fork error\n");
            exit(-1);
        } else if (pid > 0) {
            exit(0);
        }

        sleep(2);
        printf("second child, parent pid = %d\n", getppid());
        exit(0);
    }

    if (pid != waitpid(pid, NULL, 0)) {
        printf("waitpid error\n");
    }

    exit(0);
}
