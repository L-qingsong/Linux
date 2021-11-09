#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main()
{
	int fd = open("./test.txt", O_RDWR);
	if (fd == -1)
	{
		perror("open");
		exit(0);
	}

	void* pm = mmap(NULL, 4000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (pm == MAP_FAILED)
	{
		perror("mmap");
		exit(0);
	}

	pid_t pid = fork();
	if (pid > 0)
	{
		const char* msg = "hello world";
		memcpy(pm, msg, strlen(msg)+1);
	}
	else if (pid == 0)
	{
		sleep(1);
		printf("msg: %s\n", (char*)pm);
	}

	munmap(pm, 4000);
	return 0;
}
