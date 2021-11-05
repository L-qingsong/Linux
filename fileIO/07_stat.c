#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	struct stat st;
	int ret = stat("./test.txt", &st); 
	if (ret == -1)
	{
		perror("stat");
		return -1;
	}

	printf("文件大小为: %d\n", st.st_size);

	return 0;
}
