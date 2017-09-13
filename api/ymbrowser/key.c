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

int _key_open()
{
	char device[] = "/dev/input/event1"; ///<device -> device file in file systerm
	key_fd = open(device, O_RDONLY);
	if (key_fd < 0)
	{
		return -1;
	}
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
int _key_select()
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

void _key_close()
{
	close(key_fd);
}
