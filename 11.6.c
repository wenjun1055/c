#include <stdlib.h>
#include <stdio.h>

int compare_integers(void const *a, void const *b)
{
    register int const *pa = a;
    register int const *pb = b;

    return *pa > *pb ? 1 : *pa < *pb ? -1 : 0;
}

int main(){
    int *array;
    int n_values;
    int i;

    printf("how many values are there?");
    if (scanf("%d", &n_values) != 1 || n_values <= 0) {
        printf("Illegal number of values.\n"); 
        exit(EXIT_FAILURE);
    }

    array = malloc(n_values * sizeof(int));
    if (NULL == array) {
        printf("Can't get memory for that many values.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n_values; i++) {
        printf("?");
        if (scanf("%d", array + i) != 1) {
            printf("Error reading value #%d\n", i);
            free(array);
            exit(EXIT_FAILURE);
        }
    }


    qsort(array, n_values, sizeof(int), compare_integers);

    for (i = 0; i < n_values; i++) {
        printf("...%d...\n", array[i]);
    }

    free(array);
    return EXIT_SUCCESS;
}
