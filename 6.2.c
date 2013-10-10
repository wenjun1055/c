#include <stdio.h>
#include <string.h>
#include <assert.h>

int del_substr(char *str, char *substr);
int find_str(char *str, char *substr);

int main()
{
    char *str = "ABCDEFGHIJK";
    char *substr = "DBCD";

    printf("%d", find_str(str, substr));

    if (! find_str(str, substr)) {
        printf("not exists substr in str\r\n");
        return 0;
    }


}

int find_str(char *str, char *substr)
{
    int counter = 0;

    assert(str != NULL);
    if (substr == NULL) {
        return 1;
    }

    while (*str != '\0') {
        char str_char = *str;
        char substr_char = *substr;

        if (str_char == substr_char) {
            while (1) {
               str_char = *++str;
               substr_char = *++substr;
               
               if (str_char != substr_char && substr_char != '\0') {
                    break;
                }

               if ((str_char != substr_char && substr_char == '\0') || (str_char == substr_char && substr_char == '\0')) {
                    return 1;
                }
            }
        }

        str++;
    }

    return 0;
}

