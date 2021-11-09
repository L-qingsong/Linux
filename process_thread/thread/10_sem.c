#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>


struct Node
{
	int number;
	struct Node* next;
}*head;

sem_t psem;
sem_t csem;

pthread_mutex_t mutex;


void* producer(void* arg)
{
	while(1)
	{
		sem_wait(&psem);
		pthread_mutex_lock(&mutex);
		struct Node* new = (struct Node*)malloc(sizeof(struct Node));
		new->number = rand() % 100;
		new->next = head;
		head = new;
		printf("\033[35;40mproducer: tid = %ld\tnumber = %d\033[0m\n", pthread_self(), new->number);
		sem_post(&csem);
		pthread_mutex_unlock(&mutex);
		sleep(rand() % 3);
	}
	return NULL;
}

void* consumer(void* arg)
{
	while(1)
	{
		sem_wait(&csem);
		pthread_mutex_lock(&mutex);
		struct Node* pnode = head;
		printf("consumer: tid = %ld\tnumber = %d\n", pthread_self(), pnode->number);
		head = head->next;
		free(pnode);
		pnode = NULL;
		sem_post(&psem);
		pthread_mutex_unlock(&mutex);
		sleep(rand() % 3);
	}
	return NULL;
}

int main()
{
	sem_init(&psem, 0, 5);
	sem_init(&csem, 0, 0);
	pthread_mutex_init(&mutex, NULL);

	pthread_t pth[5];
	pthread_t cth[5];

	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&pth[i], NULL, producer, NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&cth[i], NULL, consumer, NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_join(pth[i], NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_join(cth[i], NULL);
	}

	sem_destroy(&psem);
	sem_destroy(&csem);

	pthread_mutex_destroy(&mutex);
	return 0;
}
