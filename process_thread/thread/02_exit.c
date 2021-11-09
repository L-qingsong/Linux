#include <stdio.h>
#include <pthread.h>

void* working(void* arg)
{
	printf("tid = %ld\n", pthread_self());

	for (int i = 0; i < 10; ++i)
	{
		if (i == 6)
		{
			pthread_exit(NULL);
		}
		printf("i = %d\n", i);
	}
	return NULL;
}
int main()
{
	printf("main tid = %ld\n", pthread_self());

	pthread_t tid;
	pthread_create(&tid, NULL, working, NULL);
	printf("success: tid = %ld\n", tid);

	for (int j = 0; j < 3; ++j)
	{
		printf("j = %d\n", j);
	}
	pthread_exit(NULL);
	return 0;
}
