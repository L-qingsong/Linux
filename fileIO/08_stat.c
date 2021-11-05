#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	struct stat myst;
	int ret = lstat(argv[1], &myst);
//	  int ret = stat(argv[1], &myst);
	if (ret == -1)
	{
		perror("stat");
		return -1;
	}
#if 0
	if (S_ISREG(myst.st_mode))
	{
		printf("这是一个普通文件\n");
	}
	if (S_ISDIR(myst.st_mode))
	{
		printf("这是一个目录文件\n");
	}
	if (S_ISBLK(myst.st_mode))
	{
		printf("这是一个块设备文件\n");
	}
	if (S_ISCHR(myst.st_mode))
	{
		printf("这是一个字符设备文件\n");
	}
	if (S_ISLNK(myst.st_mode))
	{
		printf("这是一个软链接文件\n");
	}
	if (S_ISSOCK(myst.st_mode))
	{
		printf("这是一个套接字文件\n");
	}
	if (S_ISFIFO(myst.st_mode))
	{
		printf("这是一个管道文件\n");
	}
#else
	switch (myst.st_mode & S_IFMT) 
	{
		case S_IFREG:
			printf("普通\n");
			break;
		case S_IFCHR:
			printf("字符设备\n");
			break;
		case S_IFDIR:
			printf("目录\n");
			break;
		case S_IFLNK:
			printf("软链接\n");
			break;
		case S_IFSOCK:
			printf("套接字\n");
			break;
		case S_IFBLK:
			printf("块设备\n");
			break;
		case S_IFIFO:
			printf("管道\n");
			break;
	}
#endif
	return 0;
}
