#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

//CAN配置命令
#define SETBAUD     0
#define SETMASK     1
#define SETID       3

//CAN波特率设置
#define CAN_10Kbps  0x31                                                                       
#define CAN_25Kbps  0x13
#define CAN_50Kbps  0x09
#define CAN_100Kbps 0x04
#define CAN_125Kbps 0x03
#define CAN_250Kbps 0x01
#define CAN_500Kbps 0x00

struct can_frame 
{                                                                  
    unsigned int     can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    unsigned char    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    unsigned char    __pad;   /* padding */
    unsigned char    __res0;  /* reserved / padding */
    unsigned char    __res1;  /* reserved / padding */
    unsigned char    data[8] __attribute__((aligned(8)));
};

typedef struct can_frame CanData;
int _can_open()
{
    int fd = 0;
	// 打开CAN设备文件
    fd = open("/dev/mcp2515", O_RDWR);
    if (fd < 0) {
        perror("MCP2515 open");
        exit(1);
    }
	
	return fd;
}


/* 
 * 函数名：can_setopt
 * 描  述: 设置CAN模块的波特率，标识符ID和屏蔽符
 * 输  入：
 *      canset bitrate ratevalue: 设置CAN的波特率
 *      ratevalue: 值为10、25、50、100、125、250、500，单位为Kbps
 *
 *      canset id idvalue: 设置CAN发送帧的标识符ID
 *      idvalue: 十六进制数，格式为0xFF
 *
 *      canset mask maskvalue: 设置CAN的屏蔽符
 *      maskvalue: 十六进制数，格式为0xFF
 * 返回值：程序的退出状态
 */
int _can_setopt(int fd, int rate, int id, int mask)
{
	//check if the param is legal
	if ((rate != 10 && rate != 25 && rate != 50 && rate != 100 &&
			rate != 125 && rate != 250 && rate != 500)) 
	{
		printf("The param rate:[%d] error\n", rate);
		exit(1);
	}
	if (id < 0 || id >= 2048)
	{
		printf("The param id:[%d] error\n", id);
		exit(1);
	}
	if (mask < 0 || mask >= 2048)
	{
		printf("The param mask:[%d] error!\n", mask);
		exit(1);
	}
	
 	        // 设置波特率
	switch (rate) 
	{
		case 10:
			ioctl(fd, SETBAUD, CAN_10Kbps);
			break;
		case 25:
			ioctl(fd, SETBAUD, CAN_25Kbps);
			break;
		case 50:
			ioctl(fd, SETBAUD, CAN_50Kbps);
			break;
		case 100:
			ioctl(fd, SETBAUD, CAN_100Kbps);
			break;
		case 125:
			ioctl(fd, SETBAUD, CAN_125Kbps);
			break;
		case 250:
			ioctl(fd, SETBAUD, CAN_250Kbps);
			break;
		case 500:
			ioctl(fd, SETBAUD, CAN_500Kbps);
			break;
		default:
			break;
    }

    // 设置标识符ID
	id <<= 5;
    ioctl(fd, SETID, id);


    // 设置屏蔽符
	mask <<= 5;
    ioctl(fd, SETMASK, mask);

	return 0;
}

int _can_read(int fd, char *buf, int size)
{
	int ret = 0;
	int ca_len = 0;
	
	if (fd < 0)
	{
		printf("the fd is %d error!\n", fd);
		return -1;
	}
	if (NULL == buf)
	{
		printf("buf is NULL!\n");
		return -1;
	}
	if (size < 0 || size > 8)
	{
		printf("the size is %d error!\n");
		return -1;
	}
	
	CanData cada;
	ca_len = sizeof(CanData);
	memset(&cada, 0, ca_len);
	ret = read(fd, &cada, 16);
	memcpy(buf, cada.data, strlen(cada.data));
	return strlen(cada.data);
}

int _can_write(int fd, char *buf, int size)
{
	int ret = 0;
	int ca_len = 0;
	CanData cada;
	
	if (NULL == buf)
	{
		printf("the buf is NULL!\n");
		return -1;
	}
	if (fd < 0)
	{
		printf("the fd is [%d], error!\n");
		return -1;
	}
	if (size < 0 || size > 8)
	{
		printf("the size is [%d] error!\n");
		return -1;
	}
	ca_len = sizeof(CanData);
	memset(&cada, 0, sizeof(CanData));
	memcpy(cada.data, buf, size);
	write(fd, &cada, ca_len);
	return size;
}

void _can_close(int fd)
{
	close(fd);
}

