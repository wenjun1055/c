#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    if (chdir("/tmp") < 0) {
        printf("chdir failed!\n");
        exit(-1);
    }

    printf("chidr to /tmp successed\n");
    
    return 0;
}
