#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main()
{
	key_t key = ftok(".", 0x11);
	if (key == -1)
	{
		perror("ftok");
		exit(0);
	}
	printf("key = %d\n", key);

	int shmid = shmget(key, 4096, IPC_CREAT | 0664 | IPC_EXCL);
	if (shmid == -1)
	{
		perror("shmget");
		exit(0);
	}
	printf("shmid = %d\n", shmid);

	void* ptr = shmat(shmid, NULL, 0);//SHM__RDONLY
	if (ptr == (void*)-1)
	{
		perror("shmat");
		exit(0);
	}

	int dt = shmdt(ptr);
	if (dt == -1)
	{
		perror("shmdt");
		exit(0);
	}

	system("ipcs -m");
	int ret = shmctl(shmid, IPC_RMID, NULL);
	if (ret == -1)
	{
		perror("shmctl");
		exit(0);
	}

	system("ipcs -m");
	return 0;
}
