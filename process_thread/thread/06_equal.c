#include <stdio.h>
#include <pthread.h>

int main()
{
	pthread_t tid, tid1;
	int cmp = pthread_equal(tid, tid1);
	if (cmp != 0)
	{
		printf("equal\n");
	}
	else
	{
		printf("not equal\n");
	}


	return 0;
}
