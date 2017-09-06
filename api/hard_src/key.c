/**
* @file      key.c
* @brief     This module realize the opreation of the button.
* @details   This module contains open and close and rotating training of the button.
* @author    zy
* @date      2017/06/15
* @version   HMI-T001
* @par Copyright (c)
*      keluofeite
* @par History:
*
*   version: author, date, desc\n
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

/*if you want to use debug function, you should define HMI_DEBUG_LEVEL*/
#define HMI_DEBUG_LEVEL
#include "debug.h"

/*set debug level*/

#define RETRY_NUM 4
#define test_bit(bit, array)    (array[bit/8] & (1<<(bit%8)))
static int key_fd; ///<key file descriptor

//@enum BUTTONNUM
enum BUTTONNUM{
	BUTTON_ONE=1, ///<button 1
	BUTTON_TWO,   ///<button 2
	BUTTON_THREE, ///<button 3
	BUTTON_FOUR,  ///<button 4
	BUTTON_FIVE,  ///<button 5
	BUTTON_SIX,   ///<button 6
	};
/**This is the brief of the key_open
*	int key_open()
*	this function can open the button file descriptor.
*	@param have no parama.
*	@retval  int
*	@return on success zero is returned.On error, -1 is returned.
*	@see	 
*	@note	 
*/

int key_open()
{
	char device[] = "/dev/input/event1"; ///<device -> device file in file systerm
	HMI_DEBUG("open the key device\n");
	key_fd = open(device, O_RDONLY);
	if (key_fd < 0)
	{
		HMI_ERROR("open :[%s] error!\n", device);
		return -1;
	}
	HMI_DEBUG("key_open success!\n");
	return 0;
}

/**This is the brief of the key_select
*	int key_select()
*	this function can select the button, when anyone of the buttons is pressed.
*	@param have no parama.
*	@retval  int
*	@return  on success the number which signed a button is returned.On error, -1 is returned.
*	@see	 
*	@note	 
*/
int key_select()
{
	struct input_event data; ///<data -> the struct of button info
	int type = 0;
	static int flag = 0;
	
	//select button and rerurn numbre when a button is pressed.
	read(key_fd,&data,sizeof(data));
	if (data.type==0)
		return type;
	if (data.value == 1)
	{
		flag = 1;
	}
	//if (flag==1 && data.value==0)
	if (flag==1 && data.value==0)
	{
		flag = 0;
		switch (data.code)
		{
			HMI_DEBUG("data.code:[%d]\n", data.code);
			case 1:
				HMI_DEBUG("the key:[%d] is bottoned!\n", BUTTON_ONE);
				type = BUTTON_ONE;
				break;
			case 2:
				HMI_DEBUG("the key:[%d] is bottoned!\n", BUTTON_TWO);
				type = BUTTON_TWO;
				break;
			case 14:
				HMI_DEBUG("the key:[%d] is bottoned!\n", BUTTON_THREE);
				type = BUTTON_THREE;
				break;
			case 15:
				HMI_DEBUG("the key:[%d] is bottoned!\n", BUTTON_FOUR);
				type = BUTTON_FOUR;
				break;
			case 19:
				HMI_DEBUG("the key:[%d] is bottoned!\n", BUTTON_FIVE);
				type = BUTTON_FIVE;
				break;
			case 13:
				HMI_DEBUG("the key:[%d] is bottoned!\n", BUTTON_SIX);
				type = BUTTON_SIX;
				break;
			default:
				type = -1;
				break;
		}
	}
	return type;
}

/**This is the brief of the key_close
*	int key_close()
*	this function can close the button for the next use.
*	@param have no parama.
*	@retval  void
*	@return  
*	@see	 close()
*	@note	 
*/

void key_close()
{
	close(key_fd);
	HMI_DEBUG("close device button successful!\n");
}
