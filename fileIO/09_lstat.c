#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <string.h>


#define ERRP(cond, mesg, err) do{   \
	if (cond)						\
	{								\
		perror(mesg);				\
		err;						\
	}								\
}while(0);


int main(int argc, char* argv[])
{
	ERRP(argc < 2, "参数不足", exit(1));

	struct stat myst;
	int ret = lstat(argv[1], &myst);
	ERRP(ret == -1, "lstat", goto ERR1);

	char perms[11] = {0};
	switch (myst.st_mode & S_IFMT) {
		case S_IFBLK:
			perms[0] = 'b';
			break;
		case S_IFCHR:
			perms[0] = 'c';
			break;
		case S_IFDIR:
			perms[0] = 'd';
			break;
		case S_IFREG:
			perms[0] = '-';
			break;
		case S_IFLNK:
			perms[0] = 'l';
			break;
		case S_IFSOCK:
			perms[0] = 's';
			break;
		case S_IFIFO:
			perms[0] = 'p';
			break;
		default:
			perms[0] = '?';
			break;
	}

	perms[1] = (myst.st_mode & S_IRUSR) ? 'r' : '-';
	perms[2] = (myst.st_mode & S_IWUSR) ? 'w' : '-';
	perms[3] = (myst.st_mode & S_IXUSR) ? 'x' : '-';
	perms[4] = (myst.st_mode & S_IRGRP) ? 'r' : '-';
	perms[5] = (myst.st_mode & S_IWGRP) ? 'w' : '-';
	perms[6] = (myst.st_mode & S_IXGRP) ? 'x' : '-';
	perms[7] = (myst.st_mode & S_IROTH) ? 'r' : '-';
	perms[8] = (myst.st_mode & S_IWOTH) ? 'w' : '-';
	perms[9] = (myst.st_mode & S_IXOTH) ? 'x' : '-';

	int nlink = myst.st_nlink;
	char* fileUser = getpwuid(myst.st_uid)->pw_name;
	char* fileGuser = getgrgid(myst.st_gid)->gr_name;
	int fileSize = (int)myst.st_size;
	char mtime[256] = {0};
	char* time = ctime(&myst.st_mtim.tv_sec);
	strncpy(mtime, time, strlen(time) - 1);

	char buf[1024] = {0};
	sprintf(buf, "%s %d %s %s %d %s %s", perms, nlink, fileUser, fileGuser, fileSize, mtime, argv[1]);

	printf("%s\n", buf);

	return 0;
ERR1:
	return -1;
}

