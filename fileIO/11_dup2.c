
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd1 = open(argv[1], O_RDWR|O_CREAT, 0664);
	if (fd1 == -1)
	{
		perror("open");
		exit(0);
	}

	printf("fd1 = %d\n", fd1);

	write(fd1, "hello world!", 11);
	int fd2 = 1023;
	dup2(fd1, fd2);
	if (fd2 == -1)
	{
		perror("dup");
		close(fd1);
		return -1;
	}

	close(fd1);
	const char buf[64] = {"nihao shijie"};
	open(argv[1], O_RDWR, 0664);
	write(fd2, buf, strlen(buf));
	close(fd2);
	
	return 0;
}
