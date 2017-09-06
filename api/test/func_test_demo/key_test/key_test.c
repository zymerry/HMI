#include <stdio.h>
#include "hardware_sdk.h"
#include "debug.h"

#define HMI_ALL_INFO
int main(int argc, char *argv[], char *env[])
{
	int type;
	
	//open the button
	key_open();
	
	//key select 
	while (1)
	{
		type = key_select();
		printf("error----type :[%d]\n", type);
	}
	key_close();
}
