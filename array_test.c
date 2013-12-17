#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argv, char *argc[])
{
    int i;

    printf("argv = %d\n", argv);

    printf("-----array start-----\n");
    for (i = 0 ; i < argv; i++) {
        printf("%s\n", argc[i]);
    }
    printf("-----array end-----\n\n");


    printf("-----pointer start-----\n");
    for (i = 0 ; i < argv; i++) {
        printf("%s\n", *(argc + i));
    }
    printf("-----pointer end-----\n\n");
    
    return 0;
}
