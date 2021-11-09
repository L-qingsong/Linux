#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void handler(int sig)
{
	printf("%d is catched\n", sig);
	while(1)
	{
		pid_t pid = waitpid(-1, NULL, WNOHANG);
		if (pid > 0)
		{
			printf("pid = %d is recycle\n", pid);
		}
		else if (pid == 0)
		{
			printf("no thild\n");
			break;
		}
		else if (pid == -1)
		{
			break;
		}
	}
}
int main()
{
	sigset_t myset;
	sigemptyset(&myset);
	sigaddset(&myset, SIGCHLD);
	sigprocmask(SIG_BLOCK, &myset, NULL);


	pid_t pid;
	for (int i = 0; i < 20; ++i)
	{
		pid = fork();
		if (pid == 0)
		{
			break;
		}
	}

	if (pid == 0)
	{
		printf("thild: pid = %d\n", getpid());
	}
	else if (pid > 0)
	{
		printf("parent: pid = %d\n", getpid());
		struct sigaction act;
		act.sa_handler = handler;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);
		sigaction(SIGCHLD, &act, NULL);

		sigprocmask(SIG_UNBLOCK, &myset, NULL);
		
		getchar();
	}
	return 0;
}
