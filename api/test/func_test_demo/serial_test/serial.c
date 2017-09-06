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
int serial_open(int arg)
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
		printf("/dev/ttyS1\n");
		serial_fd = open("/dev/ttyS1", O_RDWR);
	}
	else
	{
		return -1;
		printf("the arg :[%d] is error!\n", arg);
	}
	
	if (serial_fd < 0)
	{
		printf("serial_open the serial%d error!\n", arg);
	}

		fset = fcntl(serial_fd, F_SETFL, 0);	
		if (fset < 0)		
			printf("fcntl failed!\n");	
		else		
			printf("fcntl = %d\n", fset);	
#if 0		
		if (isatty(STDIN_FILENO) == 0)		
			printf("standard input is not a terminal device\n");	
		else		
			printf("isatty success!\n");
#endif		
	return serial_fd;	
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
int serial_setopt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio, oldtio;

	//parameter testing
	if (fd < 0)
	{
		printf("the fd:[%d] is error!\n", fd);
		return -1;
	}
	if (!(nSpeed==2400 || nSpeed==4800 || nSpeed==9600 ||
		nSpeed==19200 || nSpeed==57600 || nSpeed==115200 ||
		nSpeed==230400 || nSpeed==460800 || nSpeed==921600))
	{
		printf("the nSpeed :[%d] is error!\n", nSpeed);
		return -1;
	}
	if (!(nBits==7 || nBits==8))
	{
		printf("the nBits :[%d] is error!\n", nBits);
		return -1;
	}
	if (!(nEvent=='O' || nEvent=='E' || nEvent=='N'))
	{
		printf("the nEvent :[%c] is error!\n", nEvent);
		return -1;
	}
	if (!(nStop==1 || nStop==2))
	{
		printf("the nStop :[%d] is error!\n", nStop);
		return -1;
	}

	//-------start set--------
	if (tcgetattr(fd, &oldtio) != 0)
	{ 		
		perror("SetupSerial 1");		
		return -1;	
	}	
	bzero(&newtio, sizeof(newtio));
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
		printf("com set error");
		return -1;
	}
	
	printf("set successful!\n");
	return 0;
}

/**This is the brief of the serial_read
* 	int serial_read(int fd, unsigned char *buf, size_t len)
*   this function can read the 485 serial file descriptor, It can save the data on buf.
*	@param	 fd. It is the 485 serial file descriptor.
*   @param   buf. Data buf.
*   @param   len. It is the size that read.
*   @retval  int (int fd, unsigned char *buf, size_t len)
*   @return  on success realistic size that read.On error, -1 is returned.
*	@see     read()
*   @note    
*/
int serial_read(int fd, unsigned char *buf, size_t len)
{
	static struct timeval tout;
	fd_set inputs;
	int num, ret;

	//check the param
	if (fd < 0)
	{
		printf("the param fd:[%d] is error!\n", fd);
		return -1;
	}
	if (buf==NULL)
	{
		printf("the parm buf:[%s] is error!\n", buf);
		return -1;
	}

	if (len < 0)
	{
		printf("the param len :[%d] is error!\n");
		return -1;
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
		perror("select error!\n");
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
int serial_write(int fd, unsigned char *buf, size_t len)
{
	int num;

	//check the param
	if (fd < 0)
	{
		printf("the param fd:[%d] is error!\n", fd);
		return -1;
	}
	if (buf==NULL)
	{
		printf("the parm buf:[%s] is error!\n", buf);
		return -1;
	}

	if (len < 0)
	{
		printf("the param len :[%d] is error!\n");
		return -1;
	}

	//write to serial
	num = write(fd, buf, len);
	if (num < 0)
	{
		printf("write error!\n");
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
void serial_close(int fd)
{
	//check the param
	if (fd < 0)
	{
		printf("the param fd :[%d] is error!\n", fd);
	}
	else
	{
		close(fd);
	}
}

