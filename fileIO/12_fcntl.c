#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd = open(argv[1], O_RDWR|O_CREAT, 0664);
	if (fd == -1)
	{
		perror("open");
		exit(0);
	}

	printf("fd = %d\n", fd);

	write(fd, "hello world", 11);
	int fd1 = fcntl(fd, F_DUPFD);
	if (fd1 == -1)
	{
		perror("fcntl");
		exit(1);
	}
	printf("fd1 = %d\n", fd1);

	close(fd);
	getchar();
	open(argv[1], O_RDWR);
	const char buf[64] = {"nihao shijie"};
	write(fd1, buf, sizeof(buf));
	close(fd1);

	return 0;
}
