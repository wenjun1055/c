#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(void)
{
    int     c;

    while ((c = getchar()) != EOF) {
        if (isupper(c)) {
            c = tolower(c);
        }

        if (putchar(c) == EOF) {
            printf("output error\n");
            exit(-1);
        }

        if (c == '\n') {
            fflush(stdout);
        }
    }

    return 0;
}
