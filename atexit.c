#include <stdio.h>
#include <stdlib.h>

static void my_exit1(void);
static void my_exit2(void);

int main(void)
{
    if (atexit(my_exit2) != 0) {
        fprintf(stderr, "can't registery my_exit2\n");
        exit(-1);
    }


    if (atexit(my_exit1) != 0) {
        fprintf(stderr, "can't registery my_exit1\n");
        exit(-1);
    }


    if (atexit(my_exit1) != 0) {
        fprintf(stderr, "can't registery my_exit1\n");
        exit(-1);
    }

    printf("main id done\n");

    return 0;
}

static void my_exit1(void)
{
    printf("first exit handler\n");
}


static void my_exit2(void)
{
    printf("second exit handler\n");
}
