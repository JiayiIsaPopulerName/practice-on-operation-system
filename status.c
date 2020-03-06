#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
int main()
{
	int status;
	pid_t pid;
	
	pid = fork();
	if (pid < 0){perror("pid");return -1;}
	else if (pid == 0)
	{
		printf("im thinking");
		sleep(1);
		return -1;
		}
	else // 
	{
		kill(pid,SIGINT);
		wait(&status);
		
		if (WIFEXITED(status)) //子进程退出状态
		{
			printf("child exited normally with code %d\n",WEXITSTATUS(status));			
			}
			else
			{
				printf("child exited abnormally with code \n");
				if (WIFSIGNALED(status))
					printf("child exited with signal %d\n",WTERMSIG(status));		
				}
		}
	return 0;
}

