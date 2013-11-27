#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int splite_string_to_array(char *str, int len, char **array)
{
    int i = 0, counter = 0;
    char **p = array;

    while (i < len) {
        if ((long)(unsigned char)str[i] >= 224) {
            char *s = strndup(str+i, 3);
            *p = s;
            i += 3;
        } else if ((long)(unsigned char)str[i] >= 192) {
            char *s = strndup(str+i, 2);
            *p = s;
            i += 2;
        } else {
            char *s = strndup(str+i, 1);
            *p = s;
            i += 1;
        }
        p++;
    }
    
    return p - array;
}

int main()
{
    char *str = "您好啊，请问您是？";
    char **array = NULL, **p = NULL;
    int i =0, count = 0, counter = 0;

    printf("str = %s\t\tlength = %zd\n\n", str, strlen(str));

    array = (char **)calloc(sizeof(char *), strlen(str));
    p = array;
    counter = splite_string_to_array(str, strlen(str), p);
    printf("counter = %d\n", counter);

    while (*p != NULL) {
        printf("%s\n", *p);
        p++;
        count++;
    }

    for (i = 0; i < count; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}

