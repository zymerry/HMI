#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include"cJSON.h"

#define PORT 29374
#define IP "172.0.0.1" 
#define TYPE_SIZE 128
#define TYPE_DATA_SIZE 256
struct sockaddr_in server;

/*create socket*/
int init_sock(const char *ip, const int port)
{
    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sock < 0)
    {   
        perror("socket:");
        return -1; 
    }   
    
    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);
    return sock;
}


 int ApiUpdateData(char *data)
 {
    char *data_tmp = data;
    char type[TYPE_SIZE];
    char type_data[TYPE_DATA_SIZE];
    int tmp, end=0;
    int ret, sock, sock_len; //for socket
 
    /*init sock*/
    sock = init_sock(IP, PORT);
    if (sock < 0)
    {
        printf("the init_sock error!\n");
        return -1;
    }
    printf("init_sock success!\n");

    //创建一个空的文档（对象）
    cJSON *json = cJSON_CreateObject();
	
	while(end != 1)
    {
        memset(type, 0, TYPE_SIZE);
        memset(type_data, 0, TYPE_DATA_SIZE);
        tmp = strstr(data_tmp, "=") - data_tmp;
        printf("tmp:[%d]\n", tmp);
        memcpy(type, data_tmp, tmp);
        data_tmp += (tmp+1);
        if (data_tmp[0] == '\n')
        {
            data_tmp += 1;
 			cJSON_AddItemToObject(json,type,cJSON_CreateString(type_data));
            continue;
        }
        if (strstr(data_tmp, "\n"))
            tmp = strstr(data_tmp, "\n") - data_tmp;
        else
        {
            end = 1;
            tmp = strlen(data_tmp+1);
        }
        memcpy(type_data, data_tmp, tmp);
        data_tmp += (tmp+1);
        cJSON_AddItemToObject(json,type,cJSON_CreateString(type_data));
        //printf("type:[%s]\n", type);
        //printf("type_data:[%s]\n", type_data);
		//printf("------tmp:[%d]\n", tmp);
        //printf("data_tmp:[%s]\n", data_tmp);
    }

	
    //向文档中增加一个键值对{"name":"王大锤"}
    //----cJSON_AddItemToObject(json,"name",cJSON_CreateString("王大锤"));
    //向文档中添加一个键值对
    //cJSON_AddItemToObject(json,"age",cJSON_CreateNumber(29));
    //cJSON_AddNumberToObject(json,"age",29);
     
    //cJSON *array = NULL;
    //cJSON_AddItemToObject(json,"love",array=cJSON_CreateArray());
    //cJSON_AddItemToArray(array,cJSON_CreateString("LOL"));
    //cJSON_AddItemToArray(array,cJSON_CreateString("NBA"));
    //cJSON_AddItemToArray(array,cJSON_CreateString("Go shopping"));
    
    //cJSON_AddNumberToObject(json,"score",59);
    //cJSON_AddStringToObject(json,"address","beijing");
    
    //将json结构格式化到缓冲区
    char *buf = cJSON_Print(json);

	//send json
	sock_len = sizeof(struct sockaddr_in);
    ret = sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&server, sock_len);
    if (ret < 0)
    {
        perror("sendto:");
        return -1;
    }
    printf("send json success!\n");

    free(buf);
    //fclose(fp);
    //释放json结构所占用的内存
    cJSON_Delete(json);
    return 0;
 }

#if 0
int main(int argc, char *argv[], char *env[])
{
	char *data="adfasdf=hffhfdhjh\nssss=\nssdfsfdsdff=aasdfasdf";
	ApiUpdateData(data);
	return 0;
}
#endif
