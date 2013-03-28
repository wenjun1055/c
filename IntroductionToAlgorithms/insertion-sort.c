#include <stdio.h>

int main()
{
    int i;
    int a[6]={31, 41, 59, 26, 41, 58};
    for(i = 0; i < 6; i++) {
        printf("%d\t",a[i]);
    }
    printf("\n");

    int key, j = 0;
    for(j = 1; j < 6; j++) {
        key = a[j];
        i = j - 1;

        while(i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i = i - 1;
        }
        a[i+1] = key;
    }

    printf("Sort Complete!\n");
    for(i = 0; i < 6; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}
