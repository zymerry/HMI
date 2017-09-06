#include <gtest/gtest.h>
extern "C"
{
#include "hardware_sdk.h"
}

int T_key_open();
int T_key_select();
void T_key_close();
int _func_test();

int T_key_open()
{
	return key_open();
}
int T_key_select()
{
	return key_select();
}
void T_key_close()
{
	key_close();
}
int _func_test()
{
	int n = 0;

	EXPECT_EQ(0, T_key_open());
	
	while (1)
	{
		EXPECT_LE(0, n=T_key_select());
		printf("the key :[%d]\n", n);
	}
	T_key_close();
}
/*testing the param*/
//key_open
TEST(T_key_open_SUCCESS, HandleTrueReturn)
{
	EXPECT_EQ(0, T_key_open());
	EXPECT_EQ(0, T_key_open());
}

//key_select
TEST(T_key_select_SUCCESS, HandleTrueReturn)
{
	EXPECT_LE(0, T_key_select());
	EXPECT_LE(0, T_key_select());
}

//key_close
TEST(T_key_close_SUCCESS, HandleTrueReturn)
{
	//
}

/*key function test*/
TEST(T_func_test, HandleTrueReturn)
{
	_func_test();
}
int main(int argc, char *argv[], char *env[])
{
	//define the output file is xml
	testing::GTEST_FLAG(output) = "xml:";
	testing::InitGoogleTest(&argc, argv);
	//Run all tests using Google test
	return RUN_ALL_TESTS();
}
