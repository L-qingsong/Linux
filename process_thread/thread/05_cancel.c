#include <stdio.h>
#include <pthread.h>

void* working(void* arg)
{
	printf("tid = %ld\n", pthread_self());
	for (int i = 0; i < 9; ++i)
	{
		printf("i = %d\n", i);
	}
	return NULL;
}
int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, working, NULL);

	for (int i = 0; i < 9; ++i)
	{
		printf("main: i = %d\n", i);
	}
	pthread_cancel(tid);
	pthread_exit(NULL);

	return 0;
}
