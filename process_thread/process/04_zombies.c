#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int i;
	for (i = 0; i < 5; ++i)
	{
		pid = fork();
		if (pid == 0)
		{
			break;
		}
	}

	if (pid > 0)
	{
		while(1)
		{
			printf("parent: pid = [%d]\n", getpid());
			sleep(1);
		}
	}
	else if (pid == 0)
	{
		printf("third: pid = [%d] ppid = [%d]\n", getpid(), getppid());
	}
	return 0;
}
