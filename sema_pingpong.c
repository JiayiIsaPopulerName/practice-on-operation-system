#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define CNT_MAX 10

int main()
{
	int fd[2],cnt=0,semid;
	
	key_t key=0;
	key = ftok("a.txt",'d');
	if(key < 0){perror("ftok");return -1;}
	
	semid = semget(key,2,IPC_CREAT | 0666);// creat 2 semaphore object with authority read and write
    if(semid <0){perror("semc");return -3;}

	struct sembuf p1 = {0,-1,0};
	struct sembuf v1 = {0,1,0};
	struct sembuf p2 = {1,-1,0};
	struct sembuf v2 = {1,1,0};
	struct sembuf p3 = {2,-1,0};
	struct sembuf v3 = {2,1,0};

	semctl(semid,0,SETVAL,0);
	semctl(semid,1,SETVAL,0);
	semctl(semid,2,SETVAL,0);

	pid_t f,t;
	pipe(fd);
	if((f = fork()) < 0){perror("fork1");return -3;}
	if(f > 0)//father
	{	
		if((t = fork()) < 0){perror("fork2");return -4;}
		if(t == 0)//son2  
		{
			while(cnt < CNT_MAX)
			{
				semop(semid,&p3,1);
				read(fd[0],&cnt,sizeof(int));
				printf("count son2 = %d\n",cnt++);//cnt 
				write(fd[1],&cnt,sizeof(int));
				semop(semid,&v2,1);
				close(fd[1]);
				close(fd[0]);
			}
		return 0;
		}//father
		semop(semid,&p2,1);
		read(fd[0],&cnt,sizeof(int));
		printf("count father = %d\n",cnt++);//(&cnt)++)
		write(fd[1],&cnt,sizeof(int));
		semop(semid,&v1,1);
		wait(NULL);
		close(fd[1]);
		close(fd[0]);
		return 0;
	}
	else//son1
	{
		while(cnt < CNT_MAX)
		{
			semop(semid,&p1,1);
			read(fd[0],&cnt,sizeof(int));
			printf("count son1 = %d\n",cnt++);
			write(fd[1],&cnt,sizeof(int));
			semop(semid,&v3,1);
			close(fd[1]);
			close(fd[0]);
			}
			return 0;//
		}
	
	return 0;
}

