#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *ptr = (char *) malloc(1024);
    ptr[0]    = 0;
    ptr[1024] = 0;
    exit(0);
}
