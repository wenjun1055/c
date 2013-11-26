#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * strdup(char const *string)
{
    char *new_string;

    new_string = malloc(strlen(string) + 1);

    if (NULL != new_string) {
        strcpy(new_string, string);
    }

    return new_string;
}

int main()
{
    char *str = "My name is XXX";

    char *strcopy = strdup(str);
    printf("str's copy is:%s\n", strcopy);

    return 0;
}
