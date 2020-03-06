#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int fd[2];
	pid_t pid_s1;
	pipe(fd);
	
	if ((pid_s1 = fork()) == 0)
	{
		dup2(fd[1],1);
		close(fd[1]);close(fd[0]);
		execlp("ls","ls","-l",NULL);
		fprintf(stderr, "cant start ls");
	}
	else if (pid_s1 > 0)
	{
		pid_t pid_s2;
		if((pid_s2 = fork()) == 0)
		{
			dup2(fd[0],0);
			close(fd[0]);close(fd[1]);
			execlp("wc","wc",NULL);
			fprintf(stderr,"cant start wc\n");
		}
		else if (pid_s2 >0)
		{
			close(fd[0]);close(fd[1]);
			waitpid(pid_s2,NULL,0);
		}
		else{perror("fork");return -1;}
		waitpid(pid_s2,NULL,0);
	}
	else
	{perror("fork");return -1;}
return 0;
}
