#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
	int fd[2],fs[2];
	pid_t pid1,pid2,pid3;

	
	if ((pipe(fd) < 0)||(pipe(fs) < 0))
		{
			perror("pipe");
			return -1;
		}
	
	if ((pid1 = fork()) == 0)//son1
	{
		dup2(fd[1],1);
		close(fs[1]);close(fs[0]);
		close(fd[1]);close(fd[0]);
		execlp("ls","ls","-l",NULL);
		fprintf(stderr,"cant start ls");
		exit(1);//
		}
	else if (pid1 > 0)
		if ((pid2 = fork()) == 0)//son2
		{
			dup2(fd[0],0);
			close(fd[1]);close(fd[0]);
			dup2(fs[1],1);
			close(fs[1]);close(fs[0]);
			execlp("sort","sort","-n","-k","5",NULL);
			fprintf(stderr,"cant start sort");
			exit(1);//退出
			}
		if ((pid3 = fork()) == 0) //son3
		{
			dup2(fs[0],0);
			close(fd[1]);close(fd[0]);
			close(fs[1]);close(fs[0]);
			execlp("grep","grep","rwx",NULL);
			fprintf(stderr,"cant start operation");
			exit(1);//
			}
			wait(NULL);
			wait(NULL);
			wait(NULL);
			
	return 0;
}

