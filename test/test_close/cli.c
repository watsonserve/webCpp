#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "G/net/Gnet.h"

int main()
{
    int sockfd, cli, data_len;
    struct sockaddr addr;
    socklen_t len;
    char buf[BUFSIZ];

    memcpy(buf, "hello world!", 13);

    while (1)
    {
        sockfd = TCPsetCli("\x7F\x00\x00\x01", 7878);
        if (-1 == sockfd) {
            // 系统层错误
            perror("CONNECT ERROR");
            break;
        }
        send(sockfd, buf, strlen(buf), 0);
        shutdown(sockfd, SHUT_WR);
        data_len = recv(sockfd, buf, BUFSIZ, 0);
        shutdown(sockfd, SHUT_RD);
        close(sockfd);
        buf[data_len] = 0;
        printf("s: %s\n", buf);
        scanf("%s", buf);
    }
    return 0;
}
