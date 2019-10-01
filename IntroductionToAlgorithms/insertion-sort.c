#include <stdio.h>

int main()
{
    int i,n;
    printf("Enter the Number of Elements\n");
    scanf("%d",&n);
    for(i = 0; i < n; i++) {
        scanf("%d",a[i]);
    }
    printf("\n");

    int key, j = 0;
    for(j = 1; j < n; j++) {
        key = a[j];
        i = j - 1;

        while(i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i = i - 1;
        }
        a[i+1] = key;
    }

    printf("Sort Complete!\n");
    for(i = 0; i < n; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}
