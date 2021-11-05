#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int isTxt(const struct dirent* ptr)
{
	char* p = strstr(ptr->d_name, ".txt");
	if (p != NULL && *(p+4) == '\0')
	{
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("命令行参数个数 不对\n");
		return -1;
	}

	struct dirent** namelist = {0};
	int num = scandir(argv[1], &namelist, isTxt, alphasort);
	int i;
	for (i = 0; i < num; ++i)
	{
		printf("file %d : %s\n", i + 1, namelist[i]->d_name);
		free(namelist[i]);
	}
	
	printf("txt文件个数为: %d\n", num);
	free(namelist);

	return 0;
}
