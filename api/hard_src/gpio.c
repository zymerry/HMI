/**
* @file      gpio.c
* @brief     This module realize the opreation of the gpio.
* @details   This module you can you to control gpio and come true your purpose.
* @author    zy
* @date      2017/06/15
* @version   HMI-T001
* @par Copyright (c)
*      keluofeite
* @par History:
*
*   version: author, date, desc\n
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*if you want to use debug function, you should define the HMI_DEBUG_LEVEL*/
//#define HMI_DEBUG_LEVEL
#include "debug.h"

#define OUT "out"
#define IN  "in"

static char export_path[] = "/sys/class/gpio/export";
static char gpio_path[] = "/sys/class/gpio";

void select_num(int tmp, char *buf)
{
	switch (tmp)
		{
			case 1:
				memcpy(buf, "32", 2);
				break;
			case 2:
				memcpy(buf, "33", 2);
				break;
			case 3:
				memcpy(buf, "34", 2);
				break;
			case 4:
				memcpy(buf, "35", 2);
				break;
			case 5:
				memcpy(buf, "36", 2);
				break;
			case 6:
				memcpy(buf, "37", 2);
				break;
			case 7:
				memcpy(buf, "38", 2);
				break;
			case 8:
				memcpy(buf, "39", 2);
				break;
			case 9:
				memcpy(buf, "40", 2);
				break;
			case 10:
				memcpy(buf, "41", 2);
				break;
			case 11:
				memcpy(buf, "42", 2);
				break;
			default:
				break;
		}
}

/**This is the brief of the gpio_open
* 	int gpio_open(int arg)
*   this function can define a gpio.
*	@param arg. (1~11)It is the gpio num that you want to use.
*   @retval  int
*   @return  on success serial file descriptor is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int gpio_open(int arg)
{
	int fd_export;
	int fd_gpio;
	char data[8];
	char *gpio_value_path[128];
	
	//set GPB0~GPB10 -- 32~42
	if (arg < 1 || arg > 11)
	{
		HMI_ERROR("the param :[%d] arg error!\n", arg);
		return -1;
	}
	
	memset(data, 0, 8);
	memset(gpio_value_path, 0, sizeof(gpio_value_path)/sizeof(gpio_value_path[0]));
	select_num(arg, data);
	
	HMI_DEBUG("open export!\n");
	fd_export = open(export_path, O_WRONLY);
	if (fd_export < 0)
	{
		HMI_ERROR("open [%s] error!\n", export_path);
		return -1;
	}

	write(fd_export, data, strlen(data));
	close(fd_export);

	sprintf(gpio_value_path, "%s/gpio%s/%s", gpio_path, data, "value");
	//open the gpio
	HMI_DEBUG("open value!\n");
	fd_gpio = open(gpio_value_path, O_RDWR);
	if (fd_gpio < 0)
	{
		return -1;
	}
	
	return fd_gpio;
}

/**This is the brief of the gpio_setio
* 	int gpio_setio(int arg, int direction)
*   this function can define a gpio's direction.
*	@param arg. (1~11)It is the gpio num that you want to use.
*   @param direction. It is the direction (in or out).in-1 out-0
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int gpio_setio(int arg, int direction)
{
	int fd_direc; ///<director file direcriptor
	char io[8];
	char data[8];
	char direc_path[128];

	//check the param
	if (arg < 1 || arg > 11)
	{
		HMI_ERROR("the param arg :[%d] is error!\n", arg);
		return -1;
	}
	if (direction!=0 && direction!=1)
	{
		HMI_ERROR("the param direction :[%d] is error!\n", direction);
		return -1;
	}

	memset(direc_path, 0, sizeof(direc_path)/sizeof(direc_path[0]));
	memset(data, 0, 8);
	memset(io, 0, 8);

	//get the path
	select_num(arg, data);
	sprintf(direc_path, "%s/gpio%s/%s", gpio_path, data, "direction");
	HMI_DEBUG("the direc_path:[%s]\n", direc_path);

	//set the gpio direction
	HMI_DEBUG("open direction!\n");
	fd_direc = open(direc_path, O_WRONLY);
	if (fd_direc < 0)
	{
		HMI_ERROR("open direc_path:[%s] error!\n", direc_path);
		return -1;
	}

	if (direction==0)
	{
		memcpy(io, OUT, sizeof(OUT));
	}
	else
	{
		memcpy(io, IN, sizeof(IN));
	}
	write(fd_direc, io, strlen(io));
	close(fd_direc);

	return 0;
}

/**This is the brief of the gpio_read
* 	int gpio_read(int fd, char *data)
*   this function will read data from gpio.
*	@param fd. the gpio file descriptor that is opened 
*   @param data. It saves the data that read from gpio.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     read()
*   @note    
*/
int gpio_read(int fd, char *data, int size)
{
	int ret;

	//check the param
	if (fd < 0)
	{
		HMI_ERROR("the param fd:[%d] is error!\n", fd);
		return -1;
	}
	if (data==NULL)
	{
		HMI_ERROR("the param NULL!\n");
		return -1;
	}
	if (size < 0)
	{
		HMI_ERROR("the param size:[%d] is error!\n");
		return -1;
	}

	//read the gpio
	ret = read(fd, data, size);
	if (ret < 0)
	{
		HMI_ERROR("read error!\n");
		return -1;
	}
	return 0;
}

/**This is the brief of the gpio_write
* 	int gpio_write(int fd, char *data)
*   this function will write data to gpio.
*	@param fd. the gpio file descriptor that is opened 
*   @param data. It saves the data that write to gpio.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     write()
*   @note    
*/
int gpio_write(int fd, char *data)
{
	int ret;

	//check the param
	if (fd < 0)
	{
		HMI_ERROR("the param arg:[%d] is error!\n", fd);
		return -1;
	}
	if (data==NULL)
	{
		HMI_ERROR("the param NULL!\n");
		return -1;
	}

	//write the gpio
	HMI_DEBUG("data:[%s]\n", data);
	ret = write(fd, data, sizeof(data));
	if (ret < 0)
	{
		HMI_ERROR("read error!\n");
		return -1;
	}
	return 0;
}

/**This is the brief of the gpio_close
* 	void gpio_close(int gpio_fd)
*   this function will write data to gpio.
*	@param gpio_fd. the gpio file descriptor. 
*   @retval  void
*   @return
*	@see     close()
*   @note    
*/
void gpio_close(int gpio_fd)
{
	close(gpio_fd);
}

