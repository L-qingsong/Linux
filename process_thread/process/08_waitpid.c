
#include <stdio.h>
#include <sys/wait.h>
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
			int status = 0;
			int ret = waitpid(-1, &status, WNOHANG);//-1表示回收所有子进程资源同wait，status为传出参数，WNOHANG为非阻塞
			if (ret > 0)
			{
				printf("success recycle thirdPID: %d\n", ret);
				if (WIFEXITED(status))
				{
					printf("third exited code: %d\n", WEXITSTATUS(status));
				}
				if (WIFSIGNALED(status))
				{
					printf("third exited by sig: %d\n", WTERMSIG(status));
				}
			}
			else
			{
				printf("recycling failure or no third\n");
				break;
			}
			printf("parent: pid = %d\n", getpid());
		}
	}
	else if (pid == 0)
	{
		printf("third: pid = %d ppid = %d\n", getpid(), getppid());
	}
	return 0;
}
