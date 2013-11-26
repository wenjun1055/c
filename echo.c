#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    while (*++argv != NULL) {
        printf("%s\r\n", *argv);
    }

    return 0;
}
