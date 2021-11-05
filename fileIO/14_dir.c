#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
	DIR* dir = opendir(argv[1]);
	if (dir == NULL)
	{
		perror("opendir");
		return -1;
	}
//打开成功
	int count = 0;
	while(1)
	{
		struct dirent* ptr = readdir(dir);
		if (ptr == NULL)
		{
			perror("目录读完了");//读取失败也返回NULL， 并且置错误号
			break;
		}

		//读取txt文件
		if (ptr->d_type == DT_REG)
		{
			char* p = strstr(ptr->d_name, ".txt");
			if (p != NULL && *(p+4) == '\0')
			{
				count++;
				printf("第%d个文本文件为: %s\n", count, ptr->d_name);
			}
		}
	}

	printf("目录%s中文本文件的个数是%d\n", argv[1], count);

	closedir(dir);

	return EXIT_SUCCESS;
}
