#include <stdio.h>
#include <assert.h>

char *find_char(char *source, char *chars);

int main()
{
    char *source = "ABCDEF";
    char *chars  = "ESmSG";
    char *result;
    result = find_char(source, chars);
    printf("%c\r\n", *result);

    return 0;
}

char *find_char(char *source, char *chars)
{
    assert(source != NULL);
    assert(chars != NULL);

    while (*source != '\0') {
        
        char *char_tmp = chars;

        while (*char_tmp != '\0') {
            if (*source == *char_tmp) {
                return source;
            }

            char_tmp++;
        }

        source++;
    }

    return "\r\0";
}
