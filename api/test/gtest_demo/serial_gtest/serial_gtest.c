#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

extern "C"
{
#include "hardware_sdk.h"
}

static int serial_fd, serial_num;
static char file[64]={0};

int T_serial_open(int arg);
int T_serial_setopt(int fd, int nSpeed, int nBits, char nEvent, int nStop);
int T_serial_read(int fd, unsigned char *buf, size_t len);
int T_serial_write(int fd, unsigned char *buf, size_t len);
int T_serial_close(int fd);
int _func_test();

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
/*request_module*/
int T_serial_open(int arg)
{
	return serial_open(arg);
}
int T_serial_setopt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	return serial_setopt(fd, nSpeed, nBits, nEvent, nStop);
}
int T_serial_read(int fd, unsigned char *buf, size_t len)
{
	return serial_read(fd, buf, len);
}
int T_serial_write(int fd, unsigned char *buf, size_t len)
{
	return serial_write(fd, buf, len);
}
int T_serial_close(int fd)
{
	T_serial_close(fd);
	return 0;
}
int _func_test()
{
	unsigned char serial_data[256];
	int file_fd, read_size;
	unsigned char mode;
	
	memset(serial_data, 0, 256);
	do
	{
	printf("please input test mode :\n");
	printf("1--------send file!\n");
	printf("2--------receive!\n");
	mode = getchar();
	} while (mode!='1'&& mode!='2');

	switch (mode)
	{
		case '1':
			/*send file by serial*/
			//open the file to send
			printf("file:[%s]\n", file);
			file_fd = open(file, O_RDONLY);
			if (file_fd < 0)
			{
				perror("open file:");
				return -1;
			}
			//open the serial device
			EXPECT_LT(0, serial_fd = T_serial_open(serial_num));
			//set opt serial
			EXPECT_EQ(0, T_serial_setopt(serial_fd, 115200, 8, 'N', 1));
			
			if (serial_fd < 0)
			{
				printf("open serial[%d]error!\n", serial_num);
				return -1;
			}
			while ((read_size=read(file_fd, serial_data, 256))>0)
			{
				printf("------------[%s]-------------", serial_data);
				EXPECT_EQ(0, T_serial_write(serial_fd, serial_data, read_size));
				memset(serial_data, 0, 256);	
			}
			EXPECT_EQ(0, T_serial_close(serial_fd));
			break;
		case '2':
			/*receive data from serial*/
			//open the serial device
			EXPECT_LT(0, serial_fd = T_serial_open(serial_num));
			//set opt serial
			EXPECT_EQ(0, T_serial_setopt(serial_fd, 115200, 8, 'N', 1));
			while (1)
			{
				memset(serial_data, 0, 256);
				EXPECT_EQ(0, T_serial_read(serial_fd, serial_data, 256));
				if (memcpy(serial_data, "stop", 4)==0)
				{
					break;
				}
				printf("%s", serial_data);
			}
			break;
	}
	
}

/*test param*/
//serial_open
TEST(T_serial_open, Positive)
{
	EXPECT_LT(0, serial_fd = T_serial_open(serial_num));
}
TEST(T_serial_open, Negative)
{
	EXPECT_GT(0, T_serial_open(-1));
}
//serial_setopt
TEST(T_serial_setopt, Positive)
{
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 2400, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 4800, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 9600, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 19200, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 57600, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 115200, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 230400, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 460800, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 921600, 8, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 115200, 7, 'N', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 115200, 8, 'O', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 115200, 8, 'E', 1));
	EXPECT_EQ(0, T_serial_setopt(serial_fd, 115200, 8, 'N', 2));
}
TEST(T_serial_setopt, Negative)
{
	EXPECT_EQ(-1, T_serial_setopt(-1, 115200, 8, 'N', 1));
	EXPECT_EQ(-1, T_serial_setopt(serial_fd, 0, 8, 'N', 1));
	EXPECT_EQ(-1, T_serial_setopt(serial_fd, 115200, 0, 'N', 1));
	EXPECT_EQ(-1, T_serial_setopt(serial_fd, 115200, 8, 0, 1));
	EXPECT_EQ(-1, T_serial_setopt(serial_fd, 115200, 8, 'N', 0));
}
//T_serial_read
TEST(T_serial_read, Positive)
{
	unsigned char data[256];
	memset(data, 0, sizeof(data)/sizeof(data[0]));
	EXPECT_EQ(0, T_serial_read(serial_fd, data, 256));
}
TEST(T_serial_read, Negative)
{
	unsigned char data[256];
	memset(data, 0, sizeof(data)/sizeof(data[0]));
	EXPECT_EQ(-1, T_serial_read(-1, data, 256));
	EXPECT_EQ(-1, T_serial_read(serial_fd, NULL, 256));
	EXPECT_EQ(-1, T_serial_read(serial_fd, data, -1));
}
//T_serial_write
TEST(T_serial_write, Positive)
{
	unsigned char data[256];
	memset(data, 0, sizeof(data)/sizeof(data[0]));
	EXPECT_EQ(0, T_serial_write(serial_fd, data, 256));
}
TEST(T_serial_write, Negative)
{
	unsigned char data[256];
	memset(data, '1', sizeof(data)/sizeof(data[0]));
	EXPECT_EQ(-1, T_serial_write(-1, data, 256));
	EXPECT_EQ(-1, T_serial_write(serial_fd, NULL, 256));
	EXPECT_EQ(-1, T_serial_write(serial_fd, data, -1));
}
//T_serial_close
TEST(T_serial_close, Positive)
{
	EXPECT_EQ(0, T_serial_close(serial_fd));
}

/*serial function test*/
TEST(_func_test_T, Positive)
{
	_func_test();
}


int main(int argc, char *argv[], char *env[])
{
	if (argc < 3)
	{
		printf("the param num is not error!\n");
		printf("please input the num defined which serial you want to test!\n");
		printf("please input the file name which you want to send!\n");
	}
	serial_num = atoi(argv[1]);
	memcpy(file, argv[2], strlen(argv[2]));
	testing::GTEST_FLAG(output) = "xml:";
	testing::InitGoogleTest(&argc, argv);
	//Run all tests using Google test
	return RUN_ALL_TESTS();
}
