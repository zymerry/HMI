/**
* @file      serial.c
* @brief     This module realize the opreation of the serial.
* @details   This module contains open and close and set nature of the serial.
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <asm/termios.h>




//the device path in file systerm
char deviceserial1[] = "/dev/ttyUSB0";
char deviceserial2[] = "/dev/ttyS1";
	
/**This is the brief of the serial_open
* 	int serial_open(int arg);
*   this function can open the 485 serial file descriptor.
*	@param	 arg. It is the 485 serial number.It is the serial that you want to open. 		
*   @retval  int
*   @return  on success the serial file descriptor is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
static int serial_fd1;
static int serial_fd2;
int _serial_open(int arg)
{
	int serial_fd;
	int fset;

	// check param
	if (arg==1)
	{
	  	serial_fd = open("/dev/ttyUSB0", O_RDWR);
	}
	else if (arg == 2)
	{
		serial_fd = open("/dev/ttyS1", O_RDWR);
	}
	else
	{
		return -1;
	}
	
	if (serial_fd < 0)
	{
		return -1;
	}

		fset = fcntl(serial_fd, F_SETFL, 0);	
		if (fset < 0)		
            ;
#if 0		
		if (isatty(STDIN_FILENO) == 0)		
			printf("standard input is not a terminal device\n");	
		else		
			printf("isatty success!\n");
#endif		
    if (arg == 1)
    {
        serial_fd1 = serial_fd;
    }
    else if (arg == 2)
    {
        serial_fd2 = serial_fd;
    }
	return 0;	
}

/**This is the brief of the serial_setopt
* 	int serial_setopt(int fd, int nSpeed, int nBits, char nEvent, int nStop);
*   this function can set the 485 serial.The baud rate and the data bits and the odd-even check 
*   and the stop bit that you can set. 
*	@param	 fd. It is the 485 serial file descriptor.
*   @param   nSpeed. It is the baud rate.
*   @param   bBits. It is the data bits.
*   @param   nEvent. It is the odd-even check.
*   @param   nStop. It is the stop bit.
*   @retval  int
*   @return  on success zerro is returned.On error, -1 is returned.
*	@see     
*   @note    
*/
int _serial_setopt(int arg, int nSpeed, int nBits, int Evnt, int nStop)
{
    printf("in _serial_setopt\n");
    printf("arg: %d\n", arg);
    printf("nSpeed: %d\n", nSpeed);
    printf("nBits: %d\n", nBits);
    printf("nEvent: %d\n", Evnt);
    printf("nStop: %d\n", nStop);
	struct termios newtio, oldtio;
    int fd;
    char nEvent;
	//parameter testing
	if ((arg!=1)&&(arg!=2))
	{
		return -1;
	}
	if (!(nSpeed==2400 || nSpeed==4800 || nSpeed==9600 ||
		nSpeed==19200 || nSpeed==57600 || nSpeed==115200 ||
		nSpeed==230400 || nSpeed==460800 || nSpeed==921600))
	{
		return -1;
	}
	if (!(nBits==7 || nBits==8))
	{
		return -1;
	}
	//if (!(nEvent=='O' || nEvent=='E' || nEvent=='N'))
	if (!(Evnt==1 || Evnt==2 || Evnt==3))
	{
		return -1;
	}
	if (!(nStop==1 || nStop==2))
	{
        return -1;
    }
    if (Evnt == 1)
    {
        nEvent = 'O';
    }
    else if (Evnt == 2)
    {
        nEvent = 'E';
    }
    else if (Evnt == 3)
    {
        nEvent = 'N';
    }
	memset(&newtio, 0, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD; 	
	newtio.c_cflag &= ~CSIZE;

	switch (nBits)
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}

	switch (nEvent)
	{
		case 'O':
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case 'E': 
			newtio.c_iflag |= (INPCK | ISTRIP);	
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			break;
		case 'N': 
			newtio.c_cflag &= ~PARENB;
			break;
	}

	switch (nSpeed)
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 19200:
			cfsetispeed(&newtio, B19200);
			cfsetospeed(&newtio, B19200);
			break;
		case 57600:
			cfsetispeed(&newtio, B57600);
			cfsetospeed(&newtio, B57600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 230400:
			cfsetispeed(&newtio, B230400);
			cfsetospeed(&newtio, B230400);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		case 921600:
			cfsetispeed(&newtio, B921600);
			cfsetospeed(&newtio, B921600);
			break;	
	}
    if (arg == 1)
    {
        fd = serial_fd1;
    }
    else if (arg == 2)
    {
        fd = serial_fd2;
    }

	if (nStop==1)
	{
		newtio.c_cflag &= ~CSTOPB;
	}
	else if (nStop==2)
	{
		newtio.c_cflag |= CSTOPB;
	}

	//flush the fd
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd,TCIFLUSH);

	if ((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		return -1;
	}
	
	return 0;
}

/**This is the brief of the serial_read
* 	int serial_read(int fd, unsigned char *buf, size_t len)
*   this function can read the 485 serial file descriptor, It can save the data on buf.
*	@param	 fd. It is the 485 serial file descriptor.
*   @param   buf. Data buf.
*   @param   len. It is the size that read.
*   @retval  int 
*   @return  on success realistic size that read.On error, -1 is returned.
*	@see     read()
*   @note    
*/
int _serial_read(int arg, char *buf, size_t len)
{
	static struct timeval tout;
	fd_set inputs;
	int num, ret;
    int fd;
	//check the param
	if ((arg!=1)&&(arg!=2))
	{
		return -1;
	}
	if (buf==NULL)
	{
		return -1;
	}

	if (len < 0)
	{
		return -1;
	}
    if (arg == 1)
    {
        fd = serial_fd1;
    }
    else if (arg == 2)
    {
        fd = serial_fd2;
    }
	tout.tv_sec = 1;
	tout.tv_usec = 100*1000;
	
	num = 0;
	FD_ZERO(&inputs);
	FD_SET(fd, &inputs);

	//read from serial
	ret = select(fd+1, &inputs, (fd_set *)NULL, (fd_set *)NULL, &tout);
	if (ret < 0)
	{
		return -1;
	}
	if (ret > 0)
	{
		if (FD_ISSET(fd, &inputs))
		{
			num = read(fd, buf, len);
		}
	}
	return num;
}

/**This is the brief of the serial_write
* 	int serial_write(int fd, unsigned char *buf, size_t len)
*   this function can write the 485 serial file descriptor.
*	@param	 fd. It is the 485 serial file descriptor.
*   @param   buf. Data buf.
*   @param   len. It is the size that read.
*   @retval  int 
*   @return  on success realistic size that write.On error, -1 is returned.
*	@see     write()
*   @note
*/
int _serial_write(int arg, const char *buf, size_t len)
{
	int num;
    int fd;

	//check the param
	if ((arg!=1)&&(arg!=2))
	{
		return -1;
	}
	if (buf==NULL)
	{
		return -1;
	}

	if (len < 0)
	{
		return -1;
	}

    if (arg==1)
    {
        fd = serial_fd1;
    }
    else if (arg == 2)
    {
        fd = serial_fd2;
    }

	//write to serial
	num = write(fd, buf, len);
	if (num < 0)
	{
		return -1;
	}

	return num;
}

/**This is the brief of the serial_write
* 	void serial_close(int fd)
*   this function can close the 485 serial file descriptor.
*	@param	 fd. It is the 485 serial file descriptor.
*   @retval  
*   @return  
*	@see     close()
*   @note
*/
void _serial_close(int arg)
{
    int fd;
	//check the param
	if ((arg!=1)&&(arg!=2))
	{
        printf("the arg nub is error!\n");
	}
	else
	{
        if (arg == 1)
        {
            fd = serial_fd1;
        }
        else if (arg == 2)
        {
            fd = serial_fd2;
        }
		close(fd);
	}
}

