#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>



int main()
{
	char str[256];
	
	key_t key;
	key = ftok("a.txt",'h');
	if (key < 0){perror("ftok");return -1;}
	
	int shmid;
	shmid = shmget(key,sizeof(char)*256,IPC_CREAT | 0666);
	//if (shmid < 0){perror("shmget");return -2;}
	
	struct sembuf v1 = {0,1,0};
	struct sembuf p2 = {1,-1,0};
	int semid;
	semid = semget(key,2,IPC_CREAT | 0666);
	semctl(semid, 0, SETVAL, 0);
	semctl(semid, 1, SETVAL, 0);
	
	char *shmaddr;
	shmaddr = shmat(shmid,NULL,0);
	//if(shmaddr == (void*)-1){perror("shmat");return -3;}
	//*shmaddr = 0;
	
	while(1)
	{
		fgets(shmaddr,255,stdin);	
		printf("enter string%s\n",shmaddr);
		if (shmaddr[0]  == 'q')
		{
			semop(semid,&v1,1);
			break;
		}		
		semop(semid,&v1,1);
		semop(semid,&p2,1);
		if (shmaddr[0]  == 'q')
			break;
		printf("enter string%s\n",shmaddr);		
	}
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, 0, IPC_RMID, 0);
	return 0;
}

