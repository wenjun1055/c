#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *var, *value;

    if (argc == 1 || argc > 3) {
        fprintf(stderr, "usage: environ var [value]\n");
        exit(1);
    }

    var   = argv[1];
    value = getenv(var);
    if (value) {
        printf("Variable %s has value %s\n", var, value);
    } else {
        printf("Variable %s has no value\n", var);
    }

    if (argc == 3) {
        char *string;
        value  = argv[2];
        string = malloc(strlen(var) + strlen(value) + 2);
        if (!string) {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }
        strcpy(string, var);
        strcat(string, "=");
        strcat(string, value);
        printf("Calling putenv with: %s\n", string);
        if (putenv(string) != 0) {
            fprintf(stderr, "putenv failed\n");
            free(string);
            exit(1);
        }
        value = getenv(var);
        if (value) {
            printf("New value of %s is %s\n", var, value);
        } else {
            printf("New value of %s is null??\n", var);
        }
    }
    exit(0);
}
