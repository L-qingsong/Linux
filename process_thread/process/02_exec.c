#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	pid_t pid = fork();
	if (pid == 0)
	{
		int ret = execl("/bin/ps", "title", "aux", NULL);
		if (ret == -1)
		{
			perror("execl");
		}
		printf("***************\n");
		printf("***************\n");
		printf("***************\n");
		printf("***************\n");
		printf("***************\n");
	}
	else if (pid > 0)
	{
		printf("parent: pid = %d\n", getpid());
	}
	return 0;
}
