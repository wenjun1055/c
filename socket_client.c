#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4096

int main(int argc, char **argv)
{
    int     sockfd, n;
    char    recvline[4096], sendline[4096];
    struct  sockaddr_in servaddr;
    
    if (2 != argc) {
        printf("usage: ./client <ipaddress>\n");
        exit(0);
    }

    if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0))) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(6666);
    if (0 >= inet_pton(AF_INET, *(argv+1), &servaddr.sin_addr)) {
        printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    printf("send msg to server\n");
    fgets(sendline, 4096, stdin);
    if (0 > send(sockfd, sendline, strlen(sendline), 0)) {
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    close(sockfd);
    exit(0);
}
