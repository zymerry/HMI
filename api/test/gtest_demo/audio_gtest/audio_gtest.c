#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern "C"
{
#include "hardware_sdk.h"
}

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;


int audio_open_T(int *fd_dsp, int *fd_mixer);
int init_frag_T(int fd_dsp);
int audio_setdef_T(int fd_dsp, int fd_mixer);
int audio_setrate_T(int fd_dsp, int samplerate);
int audio_setsound_T(int fd_mixer, int sound);
int audio_write_T(int fd_dsp, char *buf, int write_size);
int audio_close_T(int fd_dsp, int fd_mixer);

/*global*/
static int fd_dsp, fd_mixer;
static char file[64] = {0};

int audio_open_T(int *fd_dsp, int *fd_mixer)
{
	return audio_open(fd_dsp, fd_mixer);
}
int init_frag_T(int fd_dsp)
{
	return init_frag(fd_dsp);
}
int audio_setdef_T(int fd_dsp, int fd_mixer)
{
	return audio_setdef(fd_dsp, fd_mixer);
}
int audio_setrate_T(int fd_dsp, int samplerate)
{
	return audio_setrate(fd_dsp, samplerate);
}
int audio_setsound_T(int fd_mixer, int sound)
{
	return audio_setsound(fd_mixer, sound);
}
int audio_write_T(int fd_dsp, char *buf, int write_size)
{
	return audio_write(fd_dsp, buf, write_size);
}
int audio_close_T(int fd_dsp, int fd_mixer)
{
	audio_close(fd_dsp, fd_mixer);
	return 0;
}
int _func_test()
{
	int fd, frag, ret;
	char *data = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("file:[%s]\n", file);
		perror("open file:");
		return -1;
	}
	
	//open the loudspeaker file systerm driver
	EXPECT_EQ(0, audio_open_T(&fd_dsp, &fd_mixer));
	
	//set the default nature
	EXPECT_EQ(0, audio_setdef_T(fd_dsp, fd_mixer));
	
	//get the frag
	EXPECT_LE(0, frag = init_frag_T(fd_dsp));

	//apply for the data buf
	data = (char *)malloc(frag);
	do
	{
		memset(data, 0, sizeof(data)/sizeof(data[0]));
		ret = read(fd, data, frag);
		if (ret <= 0)
		{
			break;
		}
		EXPECT_LE(0, audio_write_T(fd_dsp, data, ret));
		
	} while (1);
}

/*the param testing*/
//audio_open
TEST(audio_open_T1, Positive)
{
	EXPECT_EQ(0, audio_open_T(&fd_dsp, &fd_mixer));
}
//TEST(audio_open_T2, Negative)
//{
//	EXPECT_EQ(-1, audio_open_T(&fd_dsp, &fd_mixer));
//}

//audio_setdef_T
TEST(audio_setdef_T1, Negative)
{
	EXPECT_EQ(-1, audio_setdef_T(-1, fd_mixer));
	EXPECT_EQ(-1, audio_setdef_T(fd_dsp, -1));
	EXPECT_EQ(-1, audio_setdef_T(-1, -1));
}
TEST(audio_setdef_T2, Positive)
{
	EXPECT_EQ(0, audio_setdef_T(fd_dsp, fd_mixer));
}

//audio_setrate_T
TEST(audio_setrate_T1, Negative)
{
	EXPECT_EQ(-1, audio_setrate_T(fd_dsp, -1));
	EXPECT_EQ(-1, audio_setrate_T(-1, 16000));
	EXPECT_EQ(-1, audio_setrate_T(-1, -1));
}
TEST(audio_setrate_T2, Positive)
{
	EXPECT_EQ(0, audio_setrate_T(fd_dsp, 800));
	EXPECT_EQ(0, audio_setrate_T(fd_dsp, 11025));
	EXPECT_EQ(0, audio_setrate_T(fd_dsp, 16000));
	EXPECT_EQ(0, audio_setrate_T(fd_dsp, 22050));
	EXPECT_EQ(0, audio_setrate_T(fd_dsp, 24000));
	EXPECT_EQ(0, audio_setrate_T(fd_dsp, 32000));
	EXPECT_EQ(0, audio_setrate_T(fd_dsp, 44100));
	EXPECT_EQ(0, audio_setrate_T(fd_dsp, 48000));
}

//audio_setsound_T
TEST(audio_setsound_T1, Negative)
{
	EXPECT_EQ(-1, audio_setsound_T(-1, 0x55));
}
TEST(audio_setsound_T2, Positive)
{
	EXPECT_EQ(0, audio_setsound_T(fd_mixer, -1));
	EXPECT_EQ(0, audio_setsound_T(fd_mixer, 0));
	EXPECT_EQ(0, audio_setsound_T(fd_mixer, 0x5050));
}

//int init_frag_T
TEST(init_frag_T1, Negative)
{
	EXPECT_EQ(-1, init_frag_T(-1));
}
TEST(init_frag_T2, Positive)
{
	EXPECT_EQ(-1, init_frag_T(fd_dsp));
}

//int audio_write_T(int fd_dsp, char *buf, int write_size)
TEST(audio_write_T1, Negative)
{
	EXPECT_EQ(-1, audio_write_T(-1, "asdf", 4));
	EXPECT_EQ(-1, audio_write_T(fd_dsp, NULL, 4));
	EXPECT_EQ(-1, audio_write_T(fd_dsp, "sdf", -1));
	EXPECT_EQ(-1, audio_write_T(-1, NULL, -1));
}

//audio_close_T(int fd_dsp, int fd_mixer);
TEST(audio_close_T, HandleTrueReturn)
{
	EXPECT_EQ(0, audio_close_T(fd_dsp, fd_mixer));
}

/*test function*/
TEST(_func_test, HandleTrueReturn)
{
	_func_test();
}

int main(int argc, char *argv[], char *env[])
{
	if (argc != 2)
	{
		printf("the input param number is not two!\n");
		return -1;
	}
	
	memcpy(file, argv[1], strlen(argv[1]));
	testing::GTEST_FLAG(output) = "xml:";
	testing::InitGoogleTest(&argc, argv);
	//Run all tests using Google test
	return RUN_ALL_TESTS();
}
