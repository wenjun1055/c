//素数
#include <stdio.h>

int main()
{
    int i, avg, j, counter;
    for (i = 1; i < 101; i++) {
        if (i == 1) {
            printf("i = 1\r\n");
            continue;
        }

        avg = (int)i / 2 + 1;
        counter = 0;

        for (j = 2; j < avg; j++) {
            if (i % j == 0 && j != i) {
                counter++;
            }
        }

        if (counter == 0) {
            printf("i = %d\r\n", i);
        }
    }
    return 0;
}
