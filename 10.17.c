#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>


static volatile sig_atomic_t    sigflag;
static sigset_t                 newmask, oldmask, zeromask;

static void     sig_usr(int), tell_wait(void), tell_parent(pid_t), 
                wait_parent(void), tell_child(pid_t), wait_child();

int main(void)
{
    pid_t   pid;

    tell_wait();

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        tell_parent(getppid());
        wait_parent();

        return 0;
    }

    tell_child(pid);
    wait_child();

    return 0;
}

static void sig_usr(int signo)
{
    sigflag = 1;
}

static void tell_wait(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        printf("signal(SIGUSR1) error\n");
        exit(-1);
    }
    
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        printf("signal(SIGUSR2) error\n");
        exit(-1);
    }

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("SIG_BLOCK error\n");
        exit(-1);
    }
}

static void tell_parent(pid_t pid)
{
    kill(pid, SIGUSR2);
}

static void wait_parent(void)
{
    while (0 == sigflag) {
        sigsuspend(&zeromask);
    }

    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("SIG_SETMASK error");
        exit(-1);
    }
}

static void tell_child(pid_t pid)
{
    kill(pid, SIGUSR1);
}

static void wait_child(void)
{
    while (0 == sigflag) {
        sigsuspend(&zeromask);
    }

    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("SIG_SETMASK error");
        exit(-1);
    }
}
