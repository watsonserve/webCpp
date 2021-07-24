#include "io/StreamCache.hpp"

#ifdef __BSD__
#define the_read block_read
#endif
#ifdef __LINUX__
#define the_read putin
#endif

void G::StreamCache::setCacheFd(int fd, FdType type)
{
    this->fd = fd;
    this->type = type;
    this->offset = 0;
    this->length = 0;
}

int G::StreamCache::in_cache(ssize_t recv_siz)
{
    ssize_t len, end_off, space_siz;
    #ifdef __BSD__
    if (recv_siz < 1)
        return 0;
    #endif

    // 可写入位置
    end_off = this->offset + this->length;
    // 可写入空间
    space_siz = StreamCache::CACHESIZ - end_off;
    if (space_siz < this->offset)
    {
        // 向前迁移
        memcpy(this->buf, this->buf + this->offset, this->length);
        this->offset ^= this->offset;
        // 重新计算可写入位置
        end_off = this->length;
        // 重新计算可写入空间
        space_siz = StreamCache::CACHESIZ - end_off;
    }

    len = the_read(this->fd, this->type, this->buf + end_off, space_siz);

    #ifdef __BSD__
    if (-1 != len)
        this->unread_size += recv_siz - len;
    #endif
    this->length += len;
    return errno;
}

ssize_t G::StreamCache::read(char *dst, ssize_t len)
{
    ssize_t read_len, cp_len = this->length;
    // 从cache满足
    if (len < cp_len)
    {
        cp_len = len;
    }
    memcpy(dst, this->buf + this->offset, cp_len);
    this->length -= cp_len;
    this->offset = 0 == this->length ? 0 : this->offset + cp_len;

    len -= cp_len;
    if (!len) return cp_len;
    // 需要继续读取
    read_len = putin(fd, type, dst + cp_len, len);
    #ifdef __BSD__
    this->unread_size -= read_len;
    #endif
    return cp_len + read_len;
}
