/**
 * 证明epoll_ctl对struct epoll_event *的处理是拷贝了其内容而不是其值
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

#define FD_MUN 3

void print_x(register const void *ptr, register const int len)
{
    register int i;
    register const unsigned char *str = ((const char *)ptr);

    for (i = 0; i < len; i++)
    {
        printf("%2X ", str[i]);
    }
    printf("\n");
}

int main()
{
    const int ev_size = sizeof(struct epoll_event);
    int i, idx, epfd, nEvent;
    struct epoll_event *ev, eventList[FD_MUN];

    // 准备注册内核事件
    epfd = epoll_create(1);
    if (-1 == epfd) {
        perror("Can't create epoll");
        return -1;
    }

    ev = (struct epoll_event *)malloc(ev_size);
    memset(ev, 0, ev_size);
    ev->events = EPOLLIN | EPOLLOUT;
    ev->data.fd = 0x123456;
    print_x(ev, ev_size);

    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, ev);

    // 获取可用事件
    nEvent = epoll_wait(epfd, eventList, FD_MUN, -1);
    for (i = 0; i < nEvent; i++)
    {
        if (eventList[i].events & EPOLLERR)  // 出错
        {
            return 1;
        }

        print_x(eventList + i, ev_size);
    }

    return 0;
}