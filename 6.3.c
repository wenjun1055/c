#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *string);

int main()
{
    char *string = "ABCDEFG";
    printf("Origion:%s", string);
    reverse_string(string);
    string = strrev(*string);
    printf("Change:%s", string);

    return 0;
}

void reverse_string(char *string)
{
    char *h = string;
    char *t = string;
    char ch;

    while(*t++){};
    t--;
    t--;

    while(h < t) {
        ch = *h;
        *h++ = *t;
        *t-- = ch;
    }

    //return string;
}
