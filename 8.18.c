#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

int main(int argc, char **argv)
{
    int     i;
    setbuf(stdout, NULL);
    for (i = 1; i < argc; i++) {
        //printf("%s\n", *(argv + i));
        do_cmd(*(argv + i));
    }

    return 0;
}

static void do_cmd(char *cmd)
{
    struct tms  tmsstart, tmsend;
    clock_t     start, end;
    int         status;

    printf("\ncommand: %s\n", cmd);

    if ((start = time(&tmsstart)) == -1) {
        printf("times error\n");
        exit(-1);
    }

    if ((status = system(cmd)) < 0) {
        printf("system() error\n");
        exit(-1);
    }

    if ((end = times(&tmsend)) == -1) {
        printf("times error\n");
        exit(-1);
    }

    pr_times(end - start, &tmsstart, &tmsend);
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long     clktck = 0;
    if (0 == clktck) {
        if (0 > (clktck = sysconf(_SC_CLK_TCK))) {
            printf("sysconf error\n");
            exit(-1);
        }
    }

    printf("\t real: %7.2f\n", real / (double) clktck);
    printf("\t user: %7.2f\n", (tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
    printf("\t sys:  %7.2f\n", (tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
    printf("\t child user: %7.2f\n", (tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
    printf("\t child sys:  %7.2f\n", (tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);
}
