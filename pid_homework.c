
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	pid_t pid1,pid2,pid3,a;//定义三个进程（号）
	int fd[2];
	int fs[2]; //定义三个管道
	
	pipe(fd);
	pipe(fs);
	if((pipe(fd) == -1)||(pipe(fs) == -1))//检查管道
	{
		perror("pipe");
		return -1;	
	}
	if ((pid1 = fork()) == 0)//子进程
	{
		printf("father = %d son = %d \n", getppid(), getpid()); 
		wait(NULL);
		if((pid2 = fork()) == 0)
		{
			pid3 = getpid();
			close(fs[0]);
			close(fd[1]);
			read(fd[0],&a,sizeof(pid_t));
			write(fs[1],&pid3,sizeof(pid_t));
			close(fs[1]);
			close(fd[0]);
			printf("im grandson my pid is %d my grandfather is %d\n",getpid(),a);
		}
		else
		if (pid2 > 0)
			{
				printf("grandson = %d\n", pid2  ); 
				wait(NULL);  
			}
	}
	if (pid1 > 0)//父进程
	{
		close(fd[0]);
		close(fs[1]);
		pid1 = getpid();
		write(fd[1],&pid1,sizeof(pid_t));
		wait(NULL);
		read(fs[0],&pid3,sizeof(pid_t));
		printf("im father my pid is %d,my grandson's pid is %d\n",getpid(),pid3);
	    close(fd[1]);
		close(fs[0]);
	}

	return 0;
}
