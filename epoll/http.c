#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>

char content[] = "<head><head><title>Hello</title></head><body><strong>TEST<strong></body>";
char response[512];

int rep_err(char *err)
{
    fprintf(stderr, "%s\n", err);
    perror("ERROR");
    exit(-1);
}

int setnonblock(int fd)
{
    if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0)
        return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    uint32_t listenfd, connfd, efd, err, n, i;
    char buffer[1024];
    struct epoll_event ev, events[256];

    signal(SIGPIPE, SIG_IGN);

    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %zd\r\n\r\n%s", strlen(content), content);

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
        rep_err("create socket failed");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(80);

    if ((err = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
        rep_err("bind host failed");

    if ((err = listen(listenfd, 6)) != 0)
        rep_err("listen host failed");

    setnonblock(listenfd);

    efd = epoll_create(256);
    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &ev);

    for (;;)
    {
        n = epoll_wait(efd, events, 256, -1);
        for (i = 0; i < n; ++i)
        {
            if (events[i].data.fd == listenfd)
            {
                clilen = sizeof(cliaddr);
                if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) <= 0)
                    rep_err("accept connect failed");
                printf("CONNECT FROM %s , PORT: %d\n",
                       inet_ntop(AF_INET, &cliaddr.sin_addr, buffer, sizeof(buffer)),
                       ntohs(cliaddr.sin_port));
                setnonblock(connfd);
                ev.data.fd = connfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &ev);
            }
            else
            {
                write(events[i].data.fd, response, strlen(response));
                write(events[i].data.fd, content, strlen(content));
            }
        }
    }
    return 0;
}