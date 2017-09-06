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
* 	int key_open();
*   this function can open the button file descriptor.
*	@param
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int key_open()
{
	char device[] = "/dev/input/event1"; ///<device file in file systerm
	HMI_DEBUG("open the key device");
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
* 	int key_select();
*   this function can select the button, when anyone of the buttons is pressed 
*	the functions will return a number.
*	@param
*   @retval  int
*   @return  on success the number which signed a button is returned.On error, -1 is returned.
*	@see     select()
*   @note    
*/
int key_select()
{
	static struct input_event data; ///<the struct of button info
	static int type = 0;
	
	//select button and rerurn numbre when a button is pressed.
	HMI_DEBUG("select when a button is buttoned!\n");
	read(key_fd,&data,sizeof(data));
	if (data.type==0)
		return type;
	switch (data.code)
	{
		case 1:
			type = BUTTON_ONE;
			break;
		case 2:
			type = BUTTON_TWO;
			break;
		case 14:
			type = BUTTON_THREE;
			break;
		case 15:
			type = BUTTON_FOUR;
			break;
		case 19:
			type = BUTTON_FIVE;
			break;
		case 13:
			type = BUTTON_SIX;
			break;
		default:
			type = -1;
			break;
	}
	return type;
}

/**This is the brief of the key_close
* 	void key_close();
*   this function can close the button for the next use. 
*	@param
*   @return 
*	@see     close()
*   @note    
*/
void key_close()
{
	close(key_fd);
}
