#include <stdio.h>
#include <ctype.h>
#include <string.h>

int my_strlen(char array[]);

int main()
{
    char *sh = "123456";
    char *s  = "HelloWorld!";

    strncpy(sh, s, 11);
    printf("%d\r\n", my_strlen(sh));
}

int my_strlen(char array[])
{
    int counter = 0;
    while (array++) {
        if (isprint(*array)) {
            counter++;
        } else {
            break;
        }
    }

    
    return counter;
}
