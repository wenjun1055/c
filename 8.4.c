#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void pr_exit(int status)
{
    if (WIFEXITED(status)) {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number = %d%s\n", 
            WTERMSIG(status),
            #ifdef WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : ""
            #else 
                ""
            #endif
        
        );
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}

int main(void)
{
    pid_t   pid;
    int     status;

    if (0 > (pid = fork())) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        exit(7);
    }

    if (pid != wait(&status)) {
        printf("wait error\n");
        exit(-1);
    }

    pr_exit(status);

    if (0 > (pid = fork())) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        abort();
    }

    if (pid != wait(&status)) {
        printf("wait error\n");
        exit(-1);
    }

    pr_exit(status);


    if (0 > (pid = fork())) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        status /= 0;
    }

    if (pid != wait(&status)) {
        printf("wait error\n");
        exit(-1);
    }

    pr_exit(status);

    return 0;
}
