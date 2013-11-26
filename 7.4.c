#include <stdio.h>
#include <stdarg.h>

int max_list(int start, ...);

int main()
{
    printf("max is %d\r\n", max_list(5,11,2,56,34,999,32,-1));

    return 0;
}

int max_list(int start, ...)
{
    va_list var_arg;
    int count;
    int i = 0, max, current;

    va_start(var_arg, start);
    max = start;

    do {
        current = va_arg(var_arg, int);
        if (current > max)
            max = current;
    } while(current > 0);
    
    return max;
}
