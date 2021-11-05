#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("./test.txt", O_RDWR);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}

	
	lseek(fd, 0, SEEK_SET);
	int size = lseek(fd, 0, SEEK_END);
	if (size == -1)
	{
		perror("lseek");
	}
	printf("文件大小size = %d\n", size);
	
	close(fd);

	return 0;
}
