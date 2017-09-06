#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "hardware_sdk.h"
#include "AppUi.h"
#include "debug.h"

/*the size for uart receive*/
#define DATA_SIZE 1024*1024
#define DATA_TMP_SIZE 1024

void *key_loop(void *tmp)
{
    int ret, key_num;
    
    ret = key_open();
    if (ret < 0)
    {   
        printf("key_open errror!\n");
        return NULL;
    }   

    while (1) 
    {   
        key_num = key_select();
        switch (key_num)
        {   
            case 3:
				PageUpTurn();
                continue;
            case 4:
				PageDownTurn();
                continue;
            case 5:
				PageHomeTurn();
                continue;
            default:
                continue;
        }   
    }   
}

void *Update(void *tmp)
{
    int ret, serial_fd, sum, flag;
    char data[DATA_SIZE]; ///< one whole date received from uart
    char data_tmp[DATA_TMP_SIZE]; ///< part from one whole data

    /*init data and data_tmp*/
    memset(data_tmp, 0, DATA_TMP_SIZE);
    memset(data, 0, DATA_SIZE);

    /*open 1-serial for reciving data*/
    serial_fd = serial_open(1);
    if (serial_fd < 0)
    {   
        HMI_ERROR("serial_open error!\n");
        return NULL; 
    }   
    /*set opt of uart*/   
    ret = serial_setopt(serial_fd, 115200, 8, 'N', 1); 
    if (ret < 0)
    {
        HMI_ERROR("serial_setopt error!\n");
        return NULL;
    }
    flag = 0;

    sum = 0;
    /*receive data from uart then send*/
    //1---flag==0 means didn't receive data ever.
    //2---when receive data, set flag=1. 
    //3---if it recived whole data, in second time sending the data(when flag==1 && ret==0).
    //4---but if received data isn't whole, 
    //    you should receive data continue untile doesn't receive data(flag==1 && ret==0).
    //    then send it.
    do
    {
        memset(data_tmp, 0, DATA_TMP_SIZE);
        ret = serial_read(serial_fd, data_tmp, DATA_TMP_SIZE);
        if (ret < 0)
        {
            HMI_ERROR("serial_read error!\n");
            return NULL;
        }
        //first receive data
        else if (ret > 0 && flag==0)
        {
            flag = 1;
            memcpy(data+sum, data_tmp, ret);
            sum += ret;
        }
        //when it didn't receive whole data in one time, this whill execute
        else if (ret > 0 && flag==1)
        {
            memcpy(data+sum, data_tmp, ret);
            sum += ret;
        }
        //when received the whole data, then send
        else if (ret==0 && flag==1)
        {
            flag = 0;
            sum = 0;
            /*send data*/
			PageUpdate(data);
            memset(data, 0, DATA_SIZE);
        }
        //if didn't receive data continue while
        else if (ret==0&&flag==0)
        {
            continue;
        }
    } while (1);
}
int main(int argc, char *argv[], char *env[])
{
	int ret;
	pthread_t tid1, tid2;
    pthread_attr_t attr;
    size_t attr_size;

	/*init pthread attr*/
    ret = pthread_attr_init(&attr);
    if (ret != 0)
    {
        printf("pthread_attr_init error!\n");
        return -1;
    }
    /*set pthread for PTHREAD_CREATE_JOINABLE*/
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    if (ret != 0)
    {
        printf("pthread_attr_setdetachstate error!\n");
        return -1;
    }
    /*set pthread stack size*/
    attr_size = 1*1024*1024;
    ret = pthread_attr_setstacksize(&attr, attr_size);
    if (ret != 0)
    {
        printf("pthread_attr_setstacksize ERROR!\n");
        return -1;

    }
    /*create pthread for key loop*/
    ret = pthread_create(&tid1, &attr, key_loop, NULL);
    if (ret != 0)
    {
        printf("pthread_create tid1 error!\n");
        return -1;
    }
	/*create pthread for update*/
	ret = pthread_create(&tid2, &attr, Update, NULL);
	if (ret < 0)
	{
		printf("pthread_create tid2 error!\n");
		return -1;
	}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}

