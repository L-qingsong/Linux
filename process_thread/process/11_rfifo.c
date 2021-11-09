#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	int rfd = open("./hellofifo", O_RDONLY);
	if (rfd == -1)
	{
		perror("open");
		exit(0);
	}

	while(1)
	{
		char buf[1024] = {0};
		memset(buf, 0, sizeof(buf));
		int len = read(rfd, buf, sizeof(buf));
		if (len == 0)
		{
			printf("read finish\n");
			break;
		}
		printf("%s\n", buf);
	}
	close(rfd);
	return 0;
}
