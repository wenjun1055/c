#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    int ch;
    while ((ch = getchar()) != EOF) {
        putchar(toupper(ch));
    }
    exit(0);
}
