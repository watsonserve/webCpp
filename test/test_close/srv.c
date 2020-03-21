#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "G/net/Gnet.h"

int main()
{
    int sockfd, cli, data_len, num;
    struct sockaddr addr;
    socklen_t len;
    char buf[BUFSIZ], send_buf[BUFSIZ];

    sockfd = TCPsetup(7878);
    while (1)
    {
        cli = accept(sockfd, &addr, &len);
        if (-1 == cli) {
            // 系统层错误
            perror("accept");
            continue;
        }
        data_len = recv(cli, buf, BUFSIZ, 0);
        shutdown(sockfd, SHUT_RD);
        buf[data_len] = 0;
        sscanf(buf, "%d", &num);
        sprintf(send_buf, "{fd: %d, len: %d, content: \"%s\"}", cli, data_len, buf);
        send(cli, send_buf, strlen(send_buf), 0);
        shutdown(sockfd, SHUT_WR);
        if (3 < num)
        {
            close(num);
            printf("close %d\n", num);
            num ^= num;
        }
    }
    return 0;
}
