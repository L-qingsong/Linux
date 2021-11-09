#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int ret = mkfifo("./hellofifo", 0664);
	if (ret == -1)
	{
		perror("mkfifo");
		exit(0);
	}

	int wfd = open("./hellofifo", O_WRONLY);
	if (wfd == -1)
	{
		perror("open");
		exit(0);
	}
	int i = 0;
	while(i < 100)
	{
		char buf[1024] = {0};
		sprintf(buf, "hello fifo...%d", i);
		++i;
		write(wfd, buf, sizeof(buf));
		sleep(1);
	}
	close(wfd);
	return 0;
}
