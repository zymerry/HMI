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

int dsp_fd, mixer_fd;

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

int T_mic_open(int *dsp_fd, int *mixer_fd);
int T_mic_setopt(int samplerate, int rec_volume, int dsp_fd, int mixer_fd);
int T_mic_read(int dsp_fd, char *buf, int size);
int T_mic_close(int dsp_fd, int mixer_fd);
int _func_test();

/*request_module*/
int T_mic_open(int *dsp_fd, int *mixer_fd)
{
	return mic_open(dsp_fd, mixer_fd);
}
int T_mic_setopt(int samplerate, int rec_volume, int dsp_fd, int mixer_fd)
{
	return mic_setopt(samplerate, rec_volume, dsp_fd, mixer_fd);
}
int T_mic_read(int dsp_fd, char *buf, int size)
{
	return mic_read(dsp_fd, buf, size);
}
int T_mic_close(int dsp_fd, int mixer_fd)
{
	mic_close(dsp_fd, mixer_fd);
	return 0;
}

int _func_test()
{
	int music_fd, read_size;
	char data[1024];

	music_fd = open("/mnt/nand1-2/music", O_CREAT|O_TRUNC|O_RDWR, 0644);
	if (music_fd < 0)
	{
		perror("open /music:");
		return -1;
	}
	
	EXPECT_EQ(0, T_mic_open(&dsp_fd, &mixer_fd));
	EXPECT_EQ(0, T_mic_setopt(16000, 0x5050, dsp_fd, mixer_fd));
	while (1)
	{
		memset(data, 0, sizeof(data));
		read_size = T_mic_read(dsp_fd, data, 1024);
		if (read_size > 0)
			write(music_fd, data, 1024);
	}
}
/*the param testing*/
//mic_open
//TEST(T_mic_open_SUCCESS, HandleTrueReturn)
TEST(T_mic_open_SUCCESS, Negative)
{
	EXPECT_EQ(0, T_mic_open(&dsp_fd, &mixer_fd));
}
//mic_setopt
TEST(T_mic_setopt_TEST1, Negative)
{
	EXPECT_EQ(-1, T_mic_setopt(-5, 0x5050, dsp_fd, mixer_fd));
	EXPECT_EQ(-1, T_mic_setopt(16000, -1, dsp_fd, mixer_fd));
	EXPECT_EQ(-1, T_mic_setopt(16000, 0x5050, -1, mixer_fd));
	EXPECT_EQ(-1, T_mic_setopt(16000, 0x5050, dsp_fd, -1));
}
TEST(T_mic_setopt_TEST2, Positive)
{
	EXPECT_EQ(0, T_mic_setopt(16000, 0x5050, dsp_fd, mixer_fd));
}
//mic_read
TEST(T_mic_read_TEST1, Negative)
{
	char buf[10240];
	memset(buf, 0, 10240);

	EXPECT_EQ(-1, T_mic_read(dsp_fd, NULL, 10));
	EXPECT_EQ(-1, T_mic_read(dsp_fd, buf, -1));
	EXPECT_EQ(-1, T_mic_read(-1, buf, 10240));
}
TEST(T_mic_read_TEST2, Positive)
{
	char buf[10240];
	memset(buf, 0, 10240);
	EXPECT_LT(0, T_mic_read(dsp_fd, buf, 10240));
}
//mic_close
TEST(T_mic_close_SUCCESS, HandleTrueReturn)
{
	EXPECT_TRUE(T_mic_close(dsp_fd, mixer_fd));
}

//function test
TEST(T_FUNC_TEST, Negative)
{
	_func_test();
}

int main(int argc, char *argv[], char *env[])
{
	testing::GTEST_FLAG(output) = "xml:";
	testing::InitGoogleTest(&argc, argv);
	//Run all tests using Google test
	return RUN_ALL_TESTS();
}
