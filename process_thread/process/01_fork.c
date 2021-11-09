#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();//在fork之后的代码子进程都执行
	printf("fork返回值pid = %d\n", pid);

	if (pid > 0)
	{
		printf("parent: pid = %d\n", getpid());
	}
	else if(pid == 0)
	{
		printf("third: pid = %d, ppid = %d\n", getpid(), getppid());
	}

	int i;
	for (i = 0; i < 5; ++i)
	{
		printf("%d ", i);
		fflush(stdout);
		sleep(1);
	}
	return 0;
}
