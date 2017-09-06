#include <stdio.h>
#include <gtest/gtest.h>

extern "C"
{
#include "hardware_sdk.h"
}
#pragma once //

int test_gpio_open(int arg);
int test_gpio_setio(int arg, int direction);
int test_gpio_read(int fd, char *data, int size);
int test_gpio_write(int fd, char *data);
int void_gpio_close(int gpio_fd);
int test_gpio_setio_0(int arg);
int test_gpio_setio_1(int arg);
int test_write_0(int fd);
int test_write_1(int fd);
int test_write_null(int fd);

int test_gpio_open(int arg)
{
	return gpio_open(arg);
}
int test_gpio_setio(int arg, int direction)
{
	return gpio_setio(arg, direction);
}
int test_gpio_setio_0(int arg)
{
	return gpio_setio(arg, 0);
}
int test_gpio_setio_1(int arg)
{
	return gpio_setio(arg, 1);
}
int test_gpio_read(int fd, char *data, int size)
{
	return  gpio_read(fd, data, size);
}
int test_gpio_write(int fd, char *data)
{
	return gpio_write(fd, data);
}
void test_gpio_close(int gpio_fd)
{
	return gpio_close(gpio_fd);
}
int test_write_0(int fd)
{
	return test_gpio_write(fd, "0");
}
int test_write_1(int fd)
{
	return test_gpio_write(fd, "1");
}
int test_write_null(int fd)
{
	return test_gpio_write(fd, NULL);
}
#if 0	
class TestCase
{
public:
	
}

class UnitTest
{
public:
	
private:
}
#endif


#if 0
using ::testing::TestWithParam;
//using ::testing::range;
/*param test*/
class test_gpio_open_T : public testing::TestWithParam<int>
{
	
};

INSTANTIATE_TEST_CASE_P(0, test_gpio_open_T, testing::Values(1, 2, 3));
TEST_P(test_gpio_open_T, 0)
{
	int n = GetParam();
	EXPECT_EQ(0, test_gpio_open(n));
}
#endif
//gpio_open
TEST(test_gpio_open_SUCCESS, HandleTrueReturn)
{
	EXPECT_LT(0, test_gpio_open(1));
	EXPECT_LT(0, test_gpio_open(2));
	EXPECT_LT(0, test_gpio_open(3));
	EXPECT_LT(0, test_gpio_open(4));
	EXPECT_LT(0, test_gpio_open(5));
	EXPECT_LT(0, test_gpio_open(6));
	EXPECT_LT(0, test_gpio_open(7));
	EXPECT_LT(0, test_gpio_open(8));
	EXPECT_LT(0, test_gpio_open(9));
	EXPECT_LT(0, test_gpio_open(10));
	EXPECT_LT(0, test_gpio_open(11));
}
TEST(test_gpio_open_FAIL, HandleTrueReturn)
{
	EXPECT_LT(0, test_gpio_open(-1));
	EXPECT_LT(0, test_gpio_open(0));
	EXPECT_ANY_THROW(test_gpio_open(0));
}

//gpio_setio
TEST(test_gpio_setio_T_SUCCESS, HandleTrueReturn)
{
	EXPECT_EQ(0, test_gpio_setio_0(1));
	EXPECT_EQ(0, test_gpio_setio_0(2));
	EXPECT_EQ(0, test_gpio_setio_0(3));
	EXPECT_EQ(0, test_gpio_setio_0(4));
	EXPECT_EQ(0, test_gpio_setio_0(5));
	EXPECT_EQ(0, test_gpio_setio_0(6));
	EXPECT_EQ(0, test_gpio_setio_0(7));
	EXPECT_EQ(0, test_gpio_setio_0(8));
	EXPECT_EQ(0, test_gpio_setio_0(9));
	EXPECT_EQ(0, test_gpio_setio_0(10));
	EXPECT_EQ(0, test_gpio_setio_0(11));
	EXPECT_EQ(0, test_gpio_setio_1(1));
	EXPECT_EQ(0, test_gpio_setio_1(2));
	EXPECT_EQ(0, test_gpio_setio_1(3));
	EXPECT_EQ(0, test_gpio_setio_1(4));
	EXPECT_EQ(0, test_gpio_setio_1(5));
	EXPECT_EQ(0, test_gpio_setio_1(6));
	EXPECT_EQ(0, test_gpio_setio_1(7));
	EXPECT_EQ(0, test_gpio_setio_1(8));
	EXPECT_EQ(0, test_gpio_setio_1(9));
	EXPECT_EQ(0, test_gpio_setio_1(10));
	EXPECT_EQ(0, test_gpio_setio_1(11));
}
TEST(test_gpio_setio_T_FAIL, HandleTrueReturn)
{
	EXPECT_EQ(0, test_gpio_setio_0(0));
	EXPECT_EQ(0, test_gpio_setio_1(0));
}
//gpio_write
TEST(test_gpio_write_T, HandleTrueReturn)
{
	//test_write_0(int fd);
}

//gpio_close
TEST(test_gpio_close_T, HandleTrueReturn)
{
	//EXPECT_EQ(0, test_gpio_close(int fd))
}

//gpio_read-------didn't come true


/*death test*/
TEST(gpioDeathTest, Demo) 
{
	//EXPECT_DEATH(INSTANTIATE_TEST_CASE_P(TrueReturn, test_write_null, testing::ValuesIn(1,11), "");
	//EXPECT_DEATH(test_gpio_setio(TrueReturn,3), "");
	EXPECT_DEATH(test_gpio_open(0), "");
}

/*function test*/
int test_func_gpio()
{
	int ret;
	int fd;
	
	/*open the gpio 32*/
	EXPECT_GT(fd=test_gpio_open(1), 0);
	/*set the gpio32 is out*/
	EXPECT_EQ(test_gpio_setio(1, 0), 0);
	
	/*loop*/
	while (1)
	{
		EXPECT_GT(test_gpio_write(fd, "0"), 0);
		sleep(1);
		EXPECT_GT(test_gpio_write(fd, "1"), 0);
		sleep(1);
	}
	test_gpio_close(fd);
	return 0;
}
TEST(test_func_gpio_T, HandleTrueReturn)
{
	test_func_gpio();
}

int main(int argc, char *argv[], char *env[])
{
	testing::GTEST_FLAG(output) = "xml:";
	testing::InitGoogleTest(&argc, argv);
	//Run all tests using Google test
	return RUN_ALL_TESTS();
}

//./configure --host=arm  CC=/usr/local/arm_linux_4.2/bin/arm-linux-gcc CXX=/usr/local/arm_linux_4.2/bin/arm-linux-g++
