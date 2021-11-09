#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{
	key_t key = ftok(".", 0x22);
	if (key == -1)
	{
		perror("ftok");
		exit(0);
	}

	printf("key = %d\n", key);
	return 0;
}
