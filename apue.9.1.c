#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>


static void sig_hup(int signo)
{
    printf("SIGHUP received, pid = %d\n", getpid());
}

static void pr_ids(char *name)
{
    printf("%s: pid = %d, ppid = %d, pgrd = %d, tpgrd = %d\n", name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main(void)
{
    char    c;
    pid_t   pid;

    pr_ids("parent");
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(-1);
    } else if (pid > 0) {
        sleep(5);
        exit(0);
    } else {
        pr_ids("child");
        signal(SIGHUP, sig_hup);
        kill(getpid(), SIGTSTP);
        pr_ids("child");
        if (read(STDIN_FILENO, &c, 1) != 1 ) {
            printf("read error from controlling TTY, errno = %d\n", errno);
        }

        exit(0);
    }
}
