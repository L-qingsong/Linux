#include <stdio.h>
#include <string.h>
#include <pthread.h>


struct Persion
{
	int id;
	char name[54];
	int age;
};
void* working(void* arg)
{
	struct Persion* p = (struct Persion*)arg;

	for (int i = 0; i < 9; ++i)
	{
		printf("child: i = %d\n",   i);
		if (i == 6)
		{
			p->id = 10086;
			strcpy(p->name, "张三");
			p->age = 20;
			pthread_exit(&p);
		}
	}
	return NULL;
}
int main()
{
	pthread_t tid;
	struct Persion p;
	pthread_create(&tid, NULL, working, &p);

	void* ptr = NULL;
	pthread_join(tid, &ptr);
	struct Persion* pp = (struct Persion*)ptr;
	printf("id = %d name = %s age = %d\n", p.id, p.name, p.age);

	return 0;
}
