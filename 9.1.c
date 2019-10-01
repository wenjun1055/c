#include <stdio.h>
#include <ctype.h>

int main()
{
    int num[7] = {0,0,0,0,0,0,0};
    int i = 0;
    char string[50], *ap;
    printf("Please input a string:");
    gets(string);
    printf("...Your input string is:%s...\r\n\r\n", string);

    for (ap = string; *ap != '\0'; ap++) {
        if (iscntrl(*ap) != 0) {
            num[0]++;
        } else if (isspace(*ap) != 0) {
            num[1]++;
        } else if (isdigit(*ap) != 0) {
            num[2]++;
        } else if (islower(*ap) != 0) {
            num[3]++;
        } else if (isupper(*ap) != 0) {
            num[4]++;
        } else if (ispunct(*ap) != 0) {
            num[5]++;
        } else if (isprint(*ap) == 0) {
            num[6]++;
        }
    }

    for (i = 0; i < 7; i++) {
        printf("i = %d, num = %d\r\n", i, num[i]);
    }

    return 0;
}
