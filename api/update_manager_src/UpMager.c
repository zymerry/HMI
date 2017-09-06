/**
* @file      UpMager.c
* @brief     This module realize the update from serial.
* @details   This module contains one port to use.
* @author    zy
* @date      2017/06/15
* @version   HMI-T001
* @par Copyright (c)
*      keluofeite
* @par History:
*
*   version: author, date, desc\n
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "hardware_sdk.h"

/*if you want to use debug function, you should define HMI_DEBUG_LEVEL*/
//#define HMI_DEBUG_LEVEL
#include "debug.h"

#define CMD_LEN        128
#define FILE_PATH_LEN  128
#define FILE_NAME_LEN  256
#define SERIAL         "/dev/ttyUSB0"
#define FILE_PATH 	   "/mnt/nand1-2/update_file"
#define SYS_FILE_NAME  "sys_file.tar.gz"
#define APP_FILE_NAME  "app_file.tar.gz"
#define HTML_FILE_NAME "html_file.tar.gz"

/*set debug level*/

/**This is the brief of the SysUpgrade
*   int SysUpgrade(char type, char *data, int len, int flag)
*   this function provide the port for serial_update.
*   @param type. It is update type.'A'-system;'B'-user programmable;'C'-UI.
*   @param data. It is data for update.
*	@param len. It is len of data.
*	@param flag. It is transmisstion flag.0-before transmission;1-on transmission;2-end transmission.
*   @retval  int
*   @return on success zero is returned.On error, -1 is returned.
*   @see     
*   @note    
*/
int SysUpgrade(char type, unsigned char *data, int len, int flag)
{
	int ret, file_fd;
	static int sys_fd;	  //sys file system descriptor
	static int app_fd;	  //app file system descriptor
	static int html_fd;	  //html file system descriptor
	char file_path[FILE_PATH_LEN];
	char file_name[FILE_NAME_LEN];
	char cmd[CMD_LEN];

	/*check param type*/
	if (type!='A'&&type!='B'&&type!='C')
	{
		HMI_ERROR("the input type:[%c] is error!\n", type);
		return -1;
	}
	if (flag!=0&&flag!=1&&flag!=2)
	{
		HMI_ERROR("the input flag:[%d] is error!\n");
		return -1;
	}
	if (data==NULL)
	{
		HMI_ERROR("the input data==NULL!\n");
		return -1;
	}
	if (len < 0)
	{
		HMI_ERROR("the input len:[%d] is error!\n", len);
	}
	if (flag==0)
	{
		memset(cmd, 0, CMD_LEN);
		memset(file_path, 0, FILE_PATH_LEN);
		memset(file_name, 0, FILE_NAME_LEN);

		memcpy(file_path, FILE_PATH, strlen(FILE_PATH));
		sprintf(cmd, "mkdir -p %s", file_path);
		system(cmd);
		
		switch (type)
		{
			case 'A':
				/*systerm file for update*/
				sprintf(file_name, "%s/%s", file_path, SYS_FILE_NAME);
				sys_fd = open(file_name, O_CREAT|O_TRUNC|O_RDWR, 0644);
				if (sys_fd < 0)
				{
					HMI_ERROR("file create [%s] error!\n");
					return -1;
				}
				break;
			case 'B':
				/*app file for update*/
				sprintf(file_name, "%s/%s", file_path, APP_FILE_NAME);
				app_fd = open(file_name, O_CREAT|O_TRUNC|O_RDWR, 0644);
				if (sys_fd < 0)
				{
					HMI_ERROR("file create [%s] error!\n");
					return -1;
				}
				break;
			case 'C':
				sprintf(file_name, "%s/%s", file_path, HTML_FILE_NAME);
				html_fd = open(file_name, O_CREAT|O_TRUNC|O_RDWR, 0644);
				if (sys_fd < 0)
				{
					HMI_ERROR("file create [%s] error!\n");
					return -1;
				}
				break;
			default:
				break;
		}
	}
	else if (flag==1)
	{
		ret = 0;
		file_fd = 0;

		switch (type)
		{
			case 'A':
				file_fd = sys_fd;
				break;
			case 'B':
				file_fd = app_fd;
				break;
			case 'C':
				file_fd = html_fd;
				break;
			default:
				break;
		}

		ret = write(file_fd, data, len);
		if (ret < 0)
		{
			HMI_ERROR("write error!\n");
			return -1;
		}	
	}
	else if (flag==2)
	{
		switch (type)

		{
			case 'A':
				file_fd = sys_fd;
				break;
			case 'B':
				file_fd = app_fd;
				break;
			case 'C':
				file_fd = html_fd;
				break;
			default:
				break;
		}
		close(file_fd);
	}
	return 0;
}
