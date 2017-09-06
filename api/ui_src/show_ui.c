/**
* @file      show_ui.c
* @brief     This module realize the opreation of the page.
* @details   This module contains turn up and turn down and update of the page.
* @author    zy
* @date      2017/07/11
* @version   HMI-T001
* @par Copyright (c)
*      keluofeite
* @par History:
*
*   version: author, date, desc\n
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "cJSON.h"
#include "hardware_sdk.h"

/*the cmd and cmd_data*/
#define CMD          "cmd"
#define TYPE         "type"
#define CMD_VALUE    "PageFlush"
#define TYPE_VALUE   "request"
#define CMD_UP       "PageUpTurn"
#define CMD_DOWN     "PageDownTurn"
#define CMD_HOME     "PageHomeTurn"
#define TYPE_REQ     "request"

/*the server net info*/
#define IP   "127.0.0.1"
#define PORT 29374

/*the size of json data*/
#define SIZE 32
#define KEY_SIZE 128
#define VALUE_SIZE 256

/*the size for uart receive*/
#define DATA_SIZE 1024*1024
#define DATA_TMP_SIZE 1024

/*the remote sock info*/
static struct sockaddr_in server;

/*if you want to use debug function, you should define HMI_DEBUG_LEVEL*/
//#define DEBUG_LEVEL
#include "debug.h"

int init_sock(const char *ip, const int port)
{
	int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sock < 0)
    {   
        perror("socket:");
        return -1; 
    }   
    
    //bzero((char *) &server, sizeof(server));
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);
	
	return sock;
}

int SendJson(int sock, char *data)
{
	int sock_len, ret;
	
	sock_len = sizeof(struct sockaddr_in);
	ret = sendto(sock, data, strlen(data), 0, (struct sockaddr *)&server, sock_len);
	if (ret < 0)
	{
		HMI_ERROR("sendto error!\n");
		return -1;
	}
}

#if 0
/**This is the brief of the PageUpturn
* 	int PageUpTurn();
*   this function can realise the turn up of the page.
*	the functions will return a number.
*	@param
*   @retval  int
*   @return  on success 0 is returned. On error, -1 is returned.
*	@see     ////
*   @note    
*/
#endif
/**This is the brief of the PageUpTurn
*	int PageUpTurn()
*   this function can realise the turn up of the page.
*	@param have no parama.
*	@retval  int
*	@return  on success 0 is returnee. On error, -1 is returned.
*	@see	 ////
*	@note	 
*/

int PageUpTurn()
{
	int  ret;
	int  sock_up; ///< sock to send json
	char cmd[SIZE];  ///<“cmd”：“PageUpTurn”
	char type[SIZE]; ///<“type”：“request”
	
	/*init data*/
	memset(cmd, 0, SIZE);
	memset(type, 0, SIZE);

	/*create an empty object*/
	cJSON *json = cJSON_CreateObject();
	
	/*struct json*/
	cJSON_AddItemToObject(json, CMD, cJSON_CreateString(CMD_UP));
	cJSON_AddItemToObject(json, TYPE, cJSON_CreateString(TYPE_REQ));
	
	/*make json struct to buffer*/
	char *buf = cJSON_Print(json);
	
	/*init sock*/
	sock_up = init_sock(IP, PORT);
	if (sock_up < 0)
	{
		HMI_ERROR("init_sock error!\n");
		return -1;
	}
	
	/*send json*/
	ret = SendJson(sock_up, buf);
	if (ret < 0)
	{
		HMI_ERROR("sendJson error!\n");
		return -1;
	}
	close(sock_up);
	return 0;
}

#if 0
/**This is the brief of the PageDownturn
* 	int PageDownTurn();
*   this function can realise the turn down of the page.
*	the functions will return a number.
*	@param
*   @retval  int
*   @return  on success 0 is returned. On error, -1 is returned.
*	@see     ////
*   @note    
*/
#endif
/**This is the brief of the PageDownturn
*	int PageDownturn()
*	this function can realise the turn down of the page.
*	@param have no parama.
*	@retval  int
*	@return  on success 0 is returnee. On error, -1 is returned.
*	@see	 ////
*	@note	 
*/

int PageDownTurn()
{
	int ret;
	int sock_down; ///< sock to send json
	char cmd[SIZE];  ///<“cmd”：“PageUpTurn”
	char type[SIZE]; ///<“type”：“request”
	
	/*init data*/
	memset(cmd, 0, SIZE);
	memset(type, 0, SIZE);

	/*create an empty object*/
	cJSON *json = cJSON_CreateObject();
	
	/*struct json*/
	cJSON_AddItemToObject(json, CMD, cJSON_CreateString(CMD_DOWN));
	cJSON_AddItemToObject(json, TYPE, cJSON_CreateString(TYPE_REQ));
	
	/*make json struct to buffer*/
	char *buf = cJSON_Print(json);
	
	/*init sock*/
	sock_down = init_sock(IP, PORT);
	if (sock_down < 0)
	{
		HMI_ERROR("init_sock error!\n");
	}

	/*send json*/
	ret = SendJson(sock_down, buf);
	if (ret < 0)
	{
		HMI_ERROR("sendJson error!\n");
		return -1;
	}
	close(sock_down);
	return 0;
}

/**This is the brief of the PageHometurn
*	int PageHomeTurn()
*	this function can realise the turn up of the page.
*	@param have no parama.
*	@retval  int
*	@return  on success 0 is returnee. On error, -1 is returned.
*	@see	 ////
*	@note	 
*/

int PageHomeTurn()
{	
	int  ret;
	int  sock_home; ///< sock to send json
	char cmd[SIZE];  ///<“cmd”：“PageUpTurn”
	char type[SIZE]; ///<“type”：“request”
	
	/*init data*/
	memset(cmd, 0, SIZE);
	memset(type, 0, SIZE);

	/*create an empty object*/
	cJSON *json = cJSON_CreateObject();
	
	/*struct json*/
	cJSON_AddItemToObject(json, CMD, cJSON_CreateString(CMD_HOME));
	cJSON_AddItemToObject(json, TYPE, cJSON_CreateString(TYPE_REQ));
	
	/*make json struct to buffer*/
	char *buf = cJSON_Print(json);
	
	/*init sock*/
	sock_home = init_sock(IP, PORT);
	if (sock_home < 0)
	{
		HMI_ERROR("init_sock error!\n");
	}

	/*send json*/
	ret = SendJson(sock_home, buf);
	if (ret < 0)
	{
		HMI_ERROR("sendJson error!\n");
		return -1;
	}
	close(sock_home);
	return 0;
}

/**This is the brief of the PageUpdate
* 	int PageUpdate(char *data);
*   this function can update the page data from data. the data format should be 
*   "name=yidali|personid=123456|date=20170722|nursetype=first|checkdate=20170722|
*   medicine=arcg|doctorname=sony", the  symbol "=" you can change for update.
*	the functions will return a number.
*	@param   data is the information you want to update.
*   @retval  int
*   @return  on success 0 is returned. On error, -1 is returned.
*	@see     ////
*   @note    
*/
int PageUpdate(char *data)
{
	char *data_tmp = data;
	char key[KEY_SIZE];
   	char value[VALUE_SIZE];
   	int  ret, tmp, end=0;
   	int  update_sock, sock_len; //for socket

   	/*init sock*/
	update_sock = init_sock(IP, PORT);
	if (update_sock < 0)
	{
   		HMI_ERROR("init_sock success!\n");
	}
   	/*create an empty object*/
   	cJSON *json = cJSON_CreateObject();
	cJSON *obj = NULL;
	
	/*JSON-cmd-type---data*/		
	cJSON_AddItemToObject(json, CMD, cJSON_CreateString(CMD_VALUE));
	cJSON_AddItemToObject(json, TYPE, cJSON_CreateString(TYPE_VALUE));
	cJSON_AddItemToObject(json,"data",obj=cJSON_CreateObject());

   	//in while
   	//find the key_value by '|'
   	//different key/value by '='
   	//decide if end by end
	while(end != 1)
	{   
		memset(key, 0, KEY_SIZE);
		memset(value, 0, VALUE_SIZE);
		//tmp---offset
		tmp = strstr(data_tmp, "=") - data_tmp;
		if (tmp > 128)
		{   
			HMI_ERROR("the type is error!\n");
			return -1; 
		}
		memcpy(key, data_tmp, tmp);
		data_tmp += (tmp+1);

		/*find '|'*/
		if (strstr(data_tmp, "|"))
		{
			tmp = strstr(data_tmp, "|") - data_tmp;
			if (tmp > 256)
			{
            	HMI_ERROR("the data_type is error!\n");
            	return -1;
        	}
        }
    	else
        {
        	end = 1;
        	tmp = strlen(data_tmp);
        }
        memcpy(value, data_tmp, tmp);
        data_tmp += (tmp+1);
		/*add key-value to obj*/
		cJSON_AddItemToObject(obj, key, cJSON_CreateString(value));
	}

    /*make json struct to buffer*/
    char *buf = cJSON_Print(json);

    /*send json*/
	ret = SendJson(update_sock, buf);
	if (ret < 0)
	{
		HMI_ERROR("SendJson error!\n");
		return -1;
	}

	/*free json*/
    free(buf);
    cJSON_Delete(json);
	/*close sock*/
	close(update_sock);
    return 0;
}
