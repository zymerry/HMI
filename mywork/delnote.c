#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *env[])
{
	if (argc < 2)
	{
		printf("please input the file that you want to delnote!\n");
		return -1;
	}

	FILE *rd_fd = NULL;
	int new_fd = 0;
	char line_data[256];
	char data_tmp[256];

	new_fd = open("tmp", O_CREAT|O_TRUNC|O_RDWR);
	if (new_fd < 0)
	{
		printf("open tmp error!\n");
		return -1;
	}
	rd_fd = fopen(argv[1], "r");
	if (fd == NULL)
	{
		printf("open file:%s error!\n", argv[1]);
		return -1;
	}

	
	
	return 0;
}
