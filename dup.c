#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	int fd[2];
	pid_t pid;
	if (pipe(fd) < 0)
	{perror("pipe");return -1;}
	
	if ((pid = fork()) > 0)
	{
		dup2(fd[1],1);
		close(fd[0]);
		close(fd[1]);
		execlp("ls","ls","-l",NULL);

	}
	else if (pid == 0)
	{
		dup2(fd[0],0);
		close(fd[0]);
		close(fd[1]);
		execlp("wc","wc",NULL);
	}
	else{perror("fork");return -1;}
return 0;
}

