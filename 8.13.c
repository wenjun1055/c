#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int system(const char *cmdstring)
{
    pid_t   pid;
    int     status;

    if (NULL == cmdstring) {
        return 1;
    }

    if ((pid = fork()) < 0) {
        status = -1;
    } else if (0 == pid) {
        execl("/bin", "sh", "-C", cmdstring, (char *)0);
        _exit(127);
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;
                break;
            }
        }
    }

    return status;
}

void pr_exit(int status)
{
    if (WIFEXITED(status)) {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number = %d%s\n",-
                WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : ""
#else-
                ""
#endif
              );
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}

int main(void)
{
    int     status;

    if ((status = system("date")) < 0) {
        printf("system() error\n");
        exit(-1);
    }

    pr_exit(status);

    if ((status = system("nosuchcommand")) < 0) {
        printf("system() error\n");
        exit(-1);
    }

    pr_exit(status);

    if ((status = system("who; exit 44")) < 0) {
        printf("system() error\n");
        exit(-1);
    }

    pr_exit(status);

    return 0;
}
