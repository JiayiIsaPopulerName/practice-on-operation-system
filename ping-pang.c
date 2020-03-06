#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

#define CNT_MAX 10

volatile int flag=0;

void sig_handler(int s)
{
	signal(SIGUSR1,sig_handler);
	flag=1;
	}

void do_work(const char *str,int *cnt,int pid,int *fd)
{
	if (!flag)pause();
	flag = 0;
	read(fd[0],*cnt,sizeof(int));
	printf("%s cnt = %d",str,((*cnt)++));
	}	
int main(int argc, char **argv)
{
	int fd[2];
	if(pipe(fd)<0){perror("pipe");return -1;}
	
	pid_t pid;
	pid = fork();
	if (pid <0){perror("fork");return -1;}
	if (pid == 0)//son
		
		pid_t pid3=getpid();//grandson
		pid3 = fork();
		write(fd[1],&cnt,sizeof(int));
		
		if (pid3 <0){perror("fork");return -1;}
		if (pid3 == 0)//grandson
		
		
	else if (pid > 0)//father
	{
		while(cnt < CNT_MAX)
		{
			do_work("father",);
		}
			wait(NULL);
			close(fd[0]);
			close(fd[1]);
	}
	return 0;
}

