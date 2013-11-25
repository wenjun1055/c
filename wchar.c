#include <stdio.h>
#include <string.h>
#include <locale.h> // setlocale LC_CTYPE ¿
#include <stdlib.h> //wchar_t ¿¿¿¿
//#include <wchar.h>

int main(void)
{
    char hello[] = "你好啊";
    wchar_t c = L"你好啊";
    wchar_t *name = L"你好啊";
    printf("size of %d " , strlen(hello));

    printf("%d " , strlen(c));
    // printf("xxx %lc " , c);
    wprintf(L"test %s " , "test");
    
    setlocale(LC_CTYPE, "");
    wprintf(L"test %ls " , L"你好啊\n");
    wprintf(L"test %S " , L"你好啊\n");

    return 0;
}
