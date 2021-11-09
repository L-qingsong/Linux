#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig)
{
	printf("%d is be catch\n", sig);
}
int main()
{
	sigset_t myset;
	sigemptyset(&myset);

	sigaddset(&myset, SIGINT);
	sigaddset(&myset, SIGQUIT);
	sigaddset(&myset, SIGKILL);

	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGKILL, &act, NULL);

	sigset_t oldset;
	sigprocmask(SIG_BLOCK, &myset, &oldset);

	int i = 0;
	while(1)
	{
		sigset_t curset;
		sigpending(&curset);

		for (int i = 0; i < 32; ++i)
		{
			int ret = sigismember(&curset, i);
			printf("%d", ret);
		}

		putchar(10);
		i++;
		sleep(1);

		if (i == 10)
		{
			sigprocmask(SIG_SETMASK, &oldset, NULL);
		}
	}

	return 0;
}
