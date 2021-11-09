#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


int number;
pthread_rwlock_t rwlock;

void* writeF(void* arg)
{
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		int cur = number;
		cur++;
		number = cur;
		printf("\033[35;40mwrite: tid = %ld\tnumber = %d\033[0m\n", pthread_self(), number);
		pthread_rwlock_unlock(&rwlock);
		usleep(rand() % 100);
	}
	return NULL;
}

void* readF(void* arg)
{
	while(1)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf("read: tid = %ld\t number = %d\n", pthread_self(), number);
		pthread_rwlock_unlock(&rwlock);
		usleep(rand() % 100);
	}
	return NULL;
}
int main()
{
	pthread_t wth[3];
	pthread_t rth[5];

	for (int i = 0; i < 3; ++i)
	{
		pthread_create(&wth[i], NULL, writeF, NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&rth[i], NULL, readF, NULL);
	}

	for (int i = 0; i < 3; ++i)
	{
		pthread_join(wth[i], NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_join(rth[i], NULL);
	}

	pthread_rwlock_destroy(&rwlock);
	return 0;
}
