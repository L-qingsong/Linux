#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	//以只读方式打开文件
	int fd = open("./test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("打开文件失败\n");
		return -1;
	}
	else
	{
		printf("fd = %d\n", fd);
		char buf[1024] = {0};
		//读取文件内容到buf中
		int size = read(fd, buf, sizeof(buf));
		if (size == -1)
		{
			printf("读文件失败\n");
			return -1;
		}
		else
		{
			printf("读取到的内容为buf = %s", buf);
		}
	}
	
	//关闭文件
	close(fd);

	return 0;
}
