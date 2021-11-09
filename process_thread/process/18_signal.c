#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void working(int sig)
{
	printf("%d be catched\n", sig);
}
int main()
{
	signal(SIGALRM, working);

	struct itimerval it;
	it.it_value.tv_sec = 3;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &it, NULL);

	while(1)
	{
		sleep(100000000);
	}
	return 0;
}
