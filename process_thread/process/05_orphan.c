#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	
	if (pid > 0)
	{
		printf("parent: pid = [%d]\n", getpid());
	}
	else if (pid == 0)
	{
		sleep(1);
		printf("thild: pid = [%d] ppid = [%d]\n", getpid(), getppid());
	}

	return 0;
}
