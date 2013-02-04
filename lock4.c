#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

const char *test_file = "/tmp/test_lock";
#define SIZE_TO_TRY 5

void show_lock_info(struct flock *to_show);

int main()
{
    int file_desc;
    int res;
    struct flock region_to_test;
    int start_byte;

    file_desc = open(test_file, O_RDWR | O_CREAT, 0666);
    if (!file_desc) {
        fprintf(stderr, "Unable to open %s for read/write", test_file);
        exit(EXIT_FAILURE);
    }

    for (start_byte = 0; start_byte < 99; start_byte += SIZE_TO_TRY) {
        region_to_test.l_type   = F_WRLCK;
        region_to_test.l_whence = SEEK_SET;
        region_to_test.l_start  = start_byte;
        region_to_test.l_len    = SIZE_TO_TRY;
        region_to_test.l_pid    = -1;

        printf("Testing F_WRLK on region fromn %d to %d\n",
            start_byte, start_byte + SIZE_TO_TRY);

        res = fcntl(file_desc, F_GETLK, &region_to_test);
        if (res == -1) {
            fprintf(stderr, "F_GETLK failed\n");
            exit(EXIT_FAILURE);
        }

        if (region_to_test.l_pid != -1) {
            printf("Lock would fail. F_GETLK returned:\n");
            show_lock_info(&region_to_test);
        } else {
            printf("F_WRLK - Lock would succeed\n");
        }
        region_to_test.l_type   = F_RDLCK;
        region_to_test.l_whence = SEEK_SET;
        region_to_test.l_start  = start_byte;
        region_to_test.l_len    = SIZE_TO_TRY;
        region_to_test.l_pid    = -1;

        printf("Testing F_RDLCK on region from %d to %d\n",
            start_byte, start_byte + SIZE_TO_TRY);

        res = fcntl(file_desc, F_GETLK, &region_to_test);
        if (res == -1) {
            fprintf(stderr, "F_GETLK failed\n");
            exit(EXIT_FAILURE);
        }
        if (region_to_test.l_pid != -1) {
            printf("Lock would fail. F_GETLK returned:\n");
            show_lock_info(&region_to_test);
        } else {
            printf("F_RDLCK - Lock would succeed\n");
        }
    }
    close(file_desc);
    exit(EXIT_SUCCESS);
}

void show_lock_info(struct flock *to_show) 
{
    printf("\tl_type %d, ", to_show->l_type);
    printf("l_whence %d, ", to_show->l_whence);
    printf("l_start %d, ", (int)to_show->l_start);
    printf("l_len %d, ", (int)to_show->l_len);
    printf("l_pid %d\n", to_show->l_pid);
}
