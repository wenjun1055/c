#include <stdio.h>
#include <string.h>

int main()
{
    char *a = "abcd";
    char *b = "abcde";
    
    if (strlen(a) > strlen(b)) {
        printf("1\r\n");
    } else {
        printf("2\r\n");
    }

    //stlen的结果是个无符号数，所以操作符>=左边的表达式也将是无符号数
    //而无符号数绝不可能是负的
    if (strlen(a) - strlen(b) >= 0) {
        printf("3\r\n");
    } else {
        printf("4\r\n");
    }
}
