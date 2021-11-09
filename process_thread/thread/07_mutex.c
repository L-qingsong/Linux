#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int number = 0;
pthread_mutex_t mutex;

void* func1(void* arg)
{
	for (int i = 0; i < 50; ++i)
	{
		pthread_mutex_lock(&mutex);
		int cur = number;
		cur++;
		number = cur;
		printf("threadA: id = %ld, number = %d\n", pthread_self(), number);
		pthread_mutex_unlock(&mutex);
		usleep(10);
	}
	return NULL;
}

void* func2(void* arg)
{
	for (int i = 0; i < 50; ++i)
	{
		pthread_mutex_lock(&mutex);
		int cur = number;
		cur++;
		number = cur;
		printf("threadB: id = %ld, number = %d\n", pthread_self(), number);
		pthread_mutex_unlock(&mutex);
		usleep(10);
	}
	return NULL;
}
int main()
{
	pthread_t th1, th2;
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&th1, NULL, func1, NULL);
	pthread_create(&th2, NULL, func2, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	pthread_mutex_destroy(&mutex);
	return 0;
}
