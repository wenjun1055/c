#include <stdio.h>

int main()
{
    int number[4] = {4,10,22,45};
    int i = 0;

    for (i = 0; i < 4; i++) {
        int n = *(number + i);
        n += 5;
        n /= 10;
        printf("%s\r\n", "**********" + 10 -n);
    }
} 
