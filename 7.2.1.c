#include <stdio.h>

int gcd(int m, int n);

int main()
{
    int m,n,max;
    printf("Please input m and n:");
    scanf("%d,%d", &m, &n);
    max = gcd(m, n);
    printf("max = %d\r\n", max);

    return 0;
}

int gcd(int m, int n)
{
    if (0 >= m || 0 >= n) {
        return 0;
    }

    int r = m % n;

    if (r == 0) {
        return n;
    }

    if (r > 0) {
        return gcd(n, r);
    }
}
