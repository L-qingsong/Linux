#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* working(void* arg)
{
	printf("tid = %ld\n", pthread_self());
	for (int i = 0; i < 10; ++i)
	{
		printf("i = %d\n", i);
	}
	return NULL;
}
int main()
{
	printf("main tid = %ld\n", pthread_self());
	pthread_t tid;
	pthread_create(&tid, NULL, working, NULL);
	printf("thid = %ld\n", tid);
	for (int i = 0; i < 3;  ++i)
	{
		printf("i = %d\n", i);
	}
	sleep(1);
	return 0;
}
