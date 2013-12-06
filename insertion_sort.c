#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int issort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2))
{
    char *a = data;
    void *key;
    int i,j;

    if (NULL == (key = (char *)malloc(esize))) {
        return -1;
    }

    for (j = 1; j < size; j++) {
        memcpy(key, &a[j * esize], esize);
        i = j - 1;

        while (i >=0 && compare(&a[i * esize], key) > 0) {
            memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
            i--;
        }

        memcpy(&a[(i + 1) * esize], key, esize);
    }

    free(key);

    return 0;
}

int main()
{
    char *str = "zyxkjhaop";

    printf("original:str = %s", str);

    issort(str, 9, sizeof(char), strcmp);

    printf("changed:str = %s", str);
    
    return 0;
}
