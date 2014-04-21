#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>

#define BUFLEN  128
#define QLEN    10

#ifndef HOST_NAME_MAX
    #define HOST_NAME_MAX   256
#endif

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
    int     fd;
    int     err = 0;

    if ((fd = socket(addr->sa_family, type, 0)) < 0) {
        return -1;
    }

    if (bind(fd, addr, alen) < 0) {
        err = errno;
        goto errout;
    }

    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen(fd, qlen) < 0) {
            err = errno;
            goto errout;
        }
    }

    return fd;

errout:
    close(fd);
    errno = err;
    return -1;
}

void server(int sockfd)
{
    int     clfd;
    FILE    *fp;
    char    buf[BUFLEN];

    for (;;) {
        clfd = accept(sockfd, NULL, NULL);
        if (clfd < 0) {
            syslog(LOG_ERR, "ruptimed: accept error: %s", strerror(errno));
            return 1;
        }

        if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
            sprintf(buf, "error: %s\n", strerror(errno));
            send(clfd, buf, strlen(buf), 0);
        } else {
            while (fgets(buf, BUFLEN, fp) != NULL) {
                send(clfd, buf, strlen(buf), 0);
            }
            pclose(fp);
        }
        close(clfd);
    }
}

int main(int argc, char *argv[])
{
    struct addrinfo     *ailist, *aip;
    struct addrinfo     hint;
    int                 sockfd, err, n;
    char                *host;

    if (1 != argc) {
        printf("usage: ruptimed\n");
        exit(-1);
    }

#ifdef _SC_HOST_NAME_MAX
    n = sysconf(_SC_HOST_NAME_MAX);
    if (n < 0)
#endif
        n = HOST_NAME_MAX;
    host = malloc(n);
    if (NULL == host) {
        printf("malloc error\n");
        exit(-1);
    }

    if (gethostname(host, n) < 0) {
        printf("gethostname error\n");
        exit(-1);
    }

    daemonize("ruptimed");

    hint.ai_flags = AI_CANONNAME;
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
        syslog(LOG_ERR, "ruptime: getaddrinfo error: %s", gai_strerror(err));
        return 1;
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLEN)) >= 0) {
            serve(sockfd);
            return 0;
        }
    }

    return 1;
}
