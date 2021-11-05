#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>


int getTxtNum(const char* path);

int main(int argc, const char* argv[])
{
	int num = getTxtNum(argv[1]);
	printf("目录%s中txt文件个数为%d\n", argv[1], num);

	return 0;
}

int getTxtNum(const char* path)
{
	DIR* dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		return 0;
	}
	
	int count = 0;
	struct dirent* ptr = NULL;
	while((ptr = readdir(dir)) != NULL)
	{
		if ((strcmp(ptr->d_name, ".")) == 0 || (strcmp(ptr->d_name, "..") == 0))
		{
			continue;
		}

		if (ptr->d_type == DT_DIR)
		{
			char newPath[1024] = {0};
			sprintf(newPath, "%s/%s", path, ptr->d_name);
			count += getTxtNum(newPath);
		}
		else if (ptr->d_type == DT_REG)
		{
			char* p = strstr(ptr->d_name, ".txt");
			if (p != NULL && *(p+4) == '\0')
			{
				count++;
				printf("file %d is %s\n", count, ptr->d_name);
			}
		}
	}

	closedir(dir);
	return count;
}
