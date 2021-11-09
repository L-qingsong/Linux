#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void writeFile(int num)
{
	time_t  seconds = time(NULL);
	struct tm* loc = localtime(&seconds);
	char* time = asctime(loc);

	int fd = open("./time.log", O_WRONLY | O_CREAT | O_APPEND, 0664);
	write(fd, time, strlen(time));

	close(fd);
}

int main()
{
	pid_t pid = fork();
	if (pid > 0)
	{
		exit(0);
	}


	setsid();
	chdir(".");
	int fd = open("/dev/null", O_RDWR);
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	umask(0022);

	struct sigaction act;
	act.sa_handler = writeFile;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, NULL);

	struct itimerval it;
	it.it_interval.tv_sec = 2;
	it.it_interval.tv_usec = 0;
	it.it_value.tv_sec = 2;
	it.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &it, NULL);

	while(1)
	{
		sleep(1);
	}

	return 0;
}
