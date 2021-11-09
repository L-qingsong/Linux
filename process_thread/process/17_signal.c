#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main()
{
	sigset_t myset;
	sigemptyset(&myset);

	sigaddset(&myset, SIGINT);
	sigaddset(&myset, SIGQUIT);
	sigaddset(&myset, SIGKILL);

	sigset_t oldset;
	sigprocmask(SIG_BLOCK, &myset, &oldset);

	int i = 0;
	while(1)
	{
		sigset_t curset;
		sigpending(&curset);

		for (int i = 1; i < 32; ++i)
		{
			int ret = sigismember(&curset, i);
			printf("%d", ret);
		}
		putchar(10);
		sleep(1);
		i++;
		if (i == 10)
		{
			sigprocmask(SIG_SETMASK, &oldset, NULL);
		}
	}
	return 0;
}
