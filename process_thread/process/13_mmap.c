#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd1 = open("./hello.txt", O_RDWR);
	if (fd1 == -1)
	{
		perror("open");
		exit(0);
	}

	int size = lseek(fd1, 0 , SEEK_END);
	void* pt1 = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
	if (pt1 == MAP_FAILED)
	{
		perror("mmap");
		exit(0);
	}

	int fd2 = open("./copy.txt", O_RDWR | O_CREAT, 0664);
	if (fd2 == -1)
	{
		perror("open");
		exit(0);
	}

	ftruncate(fd2,size);
	void* pt2 = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
	if (pt2 == MAP_FAILED)
	{
		perror("mmap");
			exit(0);
	}

	memcpy(pt2, pt1, size);
	munmap(pt1, size);
	munmap(pt2, size);
	close(fd1);
	close(fd2);

	return 0;
}
