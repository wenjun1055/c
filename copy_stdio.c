#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c;
    FILE *in, *out;

    in  = fopen("1.in", "r");
    out = fopen("1.out", "w");

    while ((c = fgetc(in)) != EOF)
        fputc(c, out);

    exit(0);
}
