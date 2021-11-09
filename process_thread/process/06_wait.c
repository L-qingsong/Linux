#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
			pid_t ret = wait(NULL);
			if (ret > 0)
			{
				printf("retpid = %d\n", ret);
			}
			else
			{
				printf("fail to recycl or no thild\n");
				break;
			}
			printf("parent: pid = %d\n", getpid());
		}
	}
	else if (pid == 0)
	{
		printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
	}

	return 0;
}
