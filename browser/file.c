#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

static int flag;

int _open(char *file_name)
{
    int fd;
    fd = open(file_name, O_RDWR|O_CREAT|O_TRUNC);
    if(fd < 0)
    {
        perror("in C open file:");
        return -1;
    }
    return fd;
}

int _write(int fd, char *buf, int file_size)
{
    int ret;
    ret = write(fd, buf, file_size);
    if (ret < 0)
    {
        printf("file write error!\n");
        return -1;
    }
    return ret;
}

int _read(int fd, char *buf, int size)
{
    time_t ttm;
    struct tm *sm;
    char data[32];
    int ret;

    if (flag == 0)
    {
        flag = 1;
        ttm = time(NULL);
        sm = localtime(&ttm);
        memset(data, 0, 32);
        sprintf(data, "time  %d:%d", sm->tm_min, sm->tm_sec);
        printf("%s", data);
    }
    //ret = read(fd, buf, size);
    ret = read(fd, buf, 1024);
    if (ret < 0)
    {
        printf("read error!\n");
        return -1;
    }
    if (ret == 0)
    {
        ttm = time(NULL);
        sm = localtime(&ttm);
        memset(data, 0, 32);
        sprintf(data, "time  %d:%d\n", sm->tm_min, sm->tm_sec);
        printf("%s", data);
        sleep(500);
    }
}

void _close(int fd)
{
    close(fd);
}
