#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "G/net/Gnet.h"


SOCKET UDPsetup(const unsigned short port)
{
    int eno;
	SOCKET sockfd;
    struct sockaddr_in my_addr;

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(my_addr.sin_zero, 0, 8);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sockfd)
        return -1;
/*绑定IP地址及端口*/
    if (-1 == bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))) {
        eno = errno;
        closesocket(sockfd);
        errno = eno;
        return -1;
    }
    return sockfd;
}

SOCKET TCPsetup(const unsigned short port)
{
    int eno;
    SOCKET sockfd;
    struct sockaddr_in my_addr;

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(my_addr.sin_zero, 0, sizeof(my_addr.sin_zero));

    //创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
        return -1;

    //绑定IP地址及端口
    if (-1 == bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)))
        goto EXIT_ERR;
    
    //开始监听本机port端口
    if (-1 == listen(sockfd, 5))
        goto EXIT_ERR;

    return sockfd;

EXIT_ERR:
    eno = errno;
    closesocket(sockfd);
    errno = eno;
    return -1;
}

SOCKET UNIXsetup(const char *path)
{
    int eno;
	SOCKET sockfd;
    struct sockaddr_un my_addr;
    size_t path_len;

    memset(&my_addr, 0, sizeof(my_addr));

    // 检查长度
    path_len = strlen(path);
    if (path_len > (sizeof(my_addr.sun_path) - 1))
    {
        return -1;
    }

	my_addr.sun_family = AF_LOCAL;
    strncpy(my_addr.sun_path, path, path_len);

    // 创建套接字
    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        return -1;
    }

    // 删除路径
    unlink(path);

    // 绑定路径
    if (-1 == bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_un)))
		goto EXIT_ERR;

    // 开始监听本机port端口
    if (-1 == listen(sockfd, 5))
		goto EXIT_ERR;

    return sockfd;

EXIT_ERR:
    eno = errno;
    closesocket(sockfd);
    errno = eno;
    return -1;
}

SOCKET TCPsetCli(char * hostAddr, unsigned short port)
{
    struct sockaddr_in serv_addr;
    SOCKET sockfd;
//-------------------------------------
    sockfd = socket(AF_INET, SOCK_STREAM, 6);
    if (-1 == sockfd) {
        return -1;
    }
//创建套接字
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    memcpy((unsigned char *)&serv_addr.sin_addr, hostAddr, 4);
    memset(serv_addr.sin_zero, 0, 8);
//填表
    if (-1 == connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))) {
        return -1;
	}
    return sockfd;
}

int acceptor(SOCKET sockfd, int max, connect_callback on_conn)
{
    int errorNo;
    SOCKET clientFd;
    struct sockaddr addr;
    socklen_t len;

    max &= 0x7FFFFFFF;
    if (-1 == sockfd) {
        perror("Can't create socket");
        return -1;
    }

    // 监听循环
    while (1)
    {
        clientFd = accept(sockfd, &addr, &len);
        if (-1 == clientFd) {
            // 系统层错误
            errorNo = errno;
            perror("accept");
            // TODO
            if (EBADF == errorNo || EINVAL == errorNo)
                return -1;
            continue;
        }

        // 用户层错误
        if (max <= clientFd)
        {
            close(clientFd);
            fprintf(stderr, "Too many connect, denial of service\n");
            continue;
        }

        on_conn(clientFd, addr, len);
    }
    return 0;
}

short clean(SOCKET clinet_fd)
{
    shutdown(clinet_fd, 2);        /*0 ReadOver; 1 WriteOver; 2 RW over*/
    return closesocket(clinet_fd);
}

void killwaitcd(SOCKET cd, char *msg, unsigned long len)
{
    if(0 == len)
        len = strlen(msg);
    send(cd, msg, len, 0);
    shutdown(cd, 2);
    closesocket(cd);
    puts("\a\a\a");
    /*thread wair*/
    return;
}

unsigned short getIP4addr(char *readdr, struct sockaddr addr)
{
    unsigned char *p = (unsigned char *)&addr;
    unsigned short port = ((unsigned short*)&addr)[1];
    sprintf(readdr, "%d.%d.%d.%d", p[4], p[5], p[6], p[7]);
    return port;
}
