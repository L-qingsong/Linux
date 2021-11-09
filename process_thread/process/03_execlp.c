#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if (pid == 0)
	{
		int ret = execlp("ps", "title", "a", "u", "x", NULL);
		if (ret == -1)
		{
			perror("execlp");
		}
		printf("================\n");
		printf("================\n");
		printf("================\n");
		printf("================\n");
		printf("================\n");
	}
	else if (pid > 0)
	{
		printf("parent: pid = %d\n", getpid());
	}
	else
	{
		perror("fork");
	}
	return 0;
}
