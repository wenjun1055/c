#include <stdio.h>
#include <stdlib.h>
#include <stropts.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(void)
{
    int             s, flag;
    char            ctlbuf[BUFFSIZE], datbuf[BUFFSIZE];
    struct strbuf   ctl, dat;

    ctl.buf = ctlbuf;
    ctl.maxlen = BUFFSIZE;
    dat.buf = datbuf;
    dat.maxlen = BUFFSIZE;

    for ( ; ;) {
        flag = 0;
        if ((s = getmsg(STDIN_FILENO, &ctl, &dat, &flag)) < 0) {
            printf("getmsg error\n");
            exit(-1);
        }

        fprintf(stderr, "flag = %d, ctl.len = %d, dat.len = %d\n", flag, ctl.len, dat.len);

        if (dat.len == 0) {
            exit(0);
        } else if (dat.len > 0) {
            if (write(STDOUT_FILENO, dat.buf, dat.len) != dat.len) {
                printf("write error\n");
                exit(-1);
            }
        }
    }
}
