#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

struct Node
{
	int number;
	struct Node* next;
};
struct Node* head = NULL;

pthread_cond_t cond;
pthread_mutex_t mutex;

void* producer(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		struct Node* new = (struct Node*)malloc(sizeof(struct Node));
		new->number = rand() % 100;
		new->next = head;
		head = new;
		printf("\033[35;40mproducer: tid = %ld\tnumber = [%d]\033[0m\n", pthread_self(), new->number);
		pthread_mutex_unlock(&mutex);

		pthread_cond_broadcast(&cond);
		sleep(rand() % 3);
	}
	
	return NULL;
}

void* worker(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(head == NULL)
		{
			pthread_cond_wait(&cond, &mutex);
		}

		struct Node* pnode = head;
		printf("worker: tid = %ld\tnumber = %d\n", pthread_self(), pnode->number);
		head = head->next;
		free(pnode);
		pnode = NULL;
		pthread_mutex_unlock(&mutex);
		sleep(rand() % 3);
	}

	return NULL;
}

int main()
{
	pthread_t pth[5];
	pthread_t wth[5];
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);

	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&pth[i], NULL, producer, NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&wth[i], NULL, worker, NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_join(pth[i], NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_join(wth[i], NULL);
	}

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);

	return 0;
}
