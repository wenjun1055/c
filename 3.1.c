#include <stdio.h>
#include <unistd.h>

int main()
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("...Cannot seek...\n");
    else
        printf("...seek OK...\n");

    return 0;
}
