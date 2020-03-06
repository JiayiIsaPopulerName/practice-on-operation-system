#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define CNT_MAX  10

int main()
{
	int fd[2],semid,cnt = 0;
	key_t key;
	struct sembuf p1 = {0,-1,0};
	struct sembuf v1 = {0,1,0};
	struct sembuf p2 = {1,-1,0};
	struct sembuf v2 = {1,1,0};
	key = ftok("a.txt",'h');
	
	semid = semget(key ,2,IPC_CREAT | 0666);
	
	semctl(semid,0,SETVAL,0);
	semctl(semid,1,SETVAL,0);
	
	pipe(fd);
	
	if(fork() > 0)//不用进程号了
	{
		write(fd[1],&cnt,sizeof(int));
		semop(semid, &v1,1);//&v1,地址符号.“第v1个信号量在信号量集合里。”
		while(cnt < CNT_MAX)
		{
			semop(semid,&p2,1);
			read(fd[0],&cnt,sizeof(int));
			printf("cnt father = %d\n",cnt++);
			write(fd[1],&cnt,sizeof(int));
			semop(semid,&v1,1);
			}
			wait(NULL);
			close(fd[1]);
			close(fd[0]);
		}
	else{
		while (cnt < CNT_MAX)
		{
			semop(semid,&p1,1);
			read(fd[0],&cnt,sizeof(int));
			printf("cnt son = %d\n",cnt++);
			write(fd[1],&cnt,sizeof(int));
			semop(semid,&v2,1);
			}
			close(fd[0]);
			close(fd[1]);
			
		}
		semctl(semid,0,IPC_RMID,0);
	return 0;
}

