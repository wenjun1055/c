#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stropts.h>

#define FMNAMESZ 8

int main(int argc, char *argv[])
{
    int                 fd, i, nmods;
    struct str_list     list;

    if (2 != argc) {
        printf("usage: %s <pathname>\n", argv[0]);
        exit(-1);
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        printf("can't open %s\n", argv[1]);
        exit(-1);
    }

    if (0 == isastream(fd)) {
        printf("%s is not a stream\n", argv[1]);
        exit(-1);
    }

    if ((nmods = ioctl(fd, I_LIST, (void *)0)) < 0) {
        printf("I_LIST error for nmods\n");
        exit(-1);
    }

    printf("#modules = %d\n", nmods);

    list.sl_modlist = calloc(nmods, sizeof(struct str_mlist));
    if (NULL == list.sl_modlist) {
        printf("calloc error\n");
        exit(-1);
    }
    list.sl_nmods = nmods;

    if (ioctl(fd, I_LIST, &list) < 0) {
        printf("I_LIST error for list\n");
        exit(-1);
    }

    for (i = 1; i < nmods; i++) {
        printf(" %s: %s\n", (i == nmods) ? "deriver" : "module", list.sl_modlist++->l_name);
    }

    exit(0);
}

