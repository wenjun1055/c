#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

const char *test_file = "/tmp/test_lock";

int main()
{
    int file_desc;
    int byte_count;
    char *byte_to_write = "A";
    struct flock region_1;
    struct flock region_2;
    int res;
    
    file_desc = open(test_file, O_RDWR | O_CREAT, 0666);
    if (!file_desc) {
        fprintf(stderr, "Unable to open %s for read/write\n", test_file);
        exit(EXIT_FAILURE);
    }

    for (byte_count = 0; byte_count < 100; byte_count++) {
        (void) write(file_desc, byte_to_write, 1);
    }

    region_1.l_type   = F_RDLCK;
    region_1.l_whence = SEEK_SET;
    region_1.l_start  = 10;
    region_1.l_len    = 20;

    region_2.l_type   = F_WRLCK;
    region_2.l_whence = SEEK_SET;
    region_2.l_start  = 40;
    region_2.l_len    = 10;

    printf("Process %d locking file/n", getpid());
    res = fcntl(file_desc, F_SETLK, &region_1);
    if (res == -1) fprintf(stderr, "Failed to lock region 1\n");
    res = fcntl(file_desc, F_SETLK, &region_2);
    if (res == -1) fprintf(stderr, "Failed to lock region 2\n");
    
    sleep(60);
    printf("Process %d closing file\n", getpid());
    close(file_desc);
    exit(EXIT_SUCCESS);
}
