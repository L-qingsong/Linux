#include <stdio.h>
#include <sys/types.h>
#include <string.h>
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
	int flag = fcntl(fd, F_GETFD);
	flag = flag | O_APPEND;
	fcntl(fd, F_SETFD, flag);
	//lseek(fd, 0, SEEK_SET);
	const char buf[64] = {"nihao shijie"};
	write(fd, buf, strlen(buf));

	return 0;
}
