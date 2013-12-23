#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char    *ptr;
    int     size = 100;

    if (chdir("/home/vagrant") < 0) {
        printf("chdir failed\n");
    }

    if (getcwd(ptr, size) == NULL) {
        printf("getcwd failed\n");
    }

    printf("cwd = %s\n", ptr);

    return 0;
}
