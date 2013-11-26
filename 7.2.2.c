#include <stdio.h>

int main()
{
    int max,m,n;
    printf("Please input m and n:");
    scanf("%d,%d",&m, &n);

    if (0 >= m || 0 >= n) {
        max = 0;
    }

    max = m % n;
    while (max > 0) {
        m = n;
        n = max;

        max = m % n;
    }

    printf("%d\r\n", n);
}
