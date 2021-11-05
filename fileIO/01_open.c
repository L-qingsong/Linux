#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	//打开文件test.txt，以读写的方式，文件不存在则创建，设置文件属性
	int fd = open("test.txt", O_RDWR | O_CREAT, 0664);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}

	//打印获得的文件描述符
	printf("fd = %d\n", fd);
	close(fd);

	return 0;
}
