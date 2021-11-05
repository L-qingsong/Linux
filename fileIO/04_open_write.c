#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd1 = open("./test.txt", O_RDONLY);
	if (fd1 == -1)
	{
		printf("打开文件失败[fd1]\n");
		return -1;
	}

	int fd2 = open("./test1.txt", O_WRONLY|O_CREAT, 0664);
	if (fd2 == -1)
	{
		printf("打开文件失败[fd2]");
		return -1;
	}
	else
	{
		char buf[1024] = {0};
		int len = -1;
		while((len = read(fd1, buf, sizeof(buf))) > 0)
		{
			write(fd2, buf, sizeof(buf));
		}
		printf("buf = %s", buf);
	}

	close(fd1);
	close(fd2);

	return 0;
}
