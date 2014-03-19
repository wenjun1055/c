#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
    pid_t       pid;
    pthread_t   tid;

    pid = getpid();
    tid =-pthread_self();

    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void *arg)
{
    printids("new thread: ");
    return ((void *)0);
}

int main(void)
{
    int     err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (0 != err) {
        printf("can't create thread :%s\n", strerror(err));
        exit(-1);
    }

    printids("main thread: ");
    sleep(1);

    return 0;
}
