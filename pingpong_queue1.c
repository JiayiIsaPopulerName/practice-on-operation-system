#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	key_t key;
	int semid,shmid;
	struct sembuf v2 = {1,1,0};
	struct sembuf p1 = {0,-1,0};
	
	int *shmaddr;
	int cnt = 0;
	
	key = ftok("a.txt",'t');
	if (key < 0){perror("ftok");exit(-1);}
	shmid = shmget (key, sizeof(int), 0666 | IPC_CREAT);
	if (shmid <0 ){perror("shmid");exit(-1);}
	semid = semget(key,2,0666 | IPC_CREAT);
	if (semid < 0){perror("semget");return -1;}
	
	semctl(semid, 1, SETVAL, 0);
	
	shmaddr = shmat(shmid,NULL,0);
	if (shmaddr == (void*)-1){perror("shmaddr");return -1;}
	
	do
	{
		semop(semid,&p1,1);//waiting first pross
		if (shmaddr[0] == -1)
		{
			shmdt(shmaddr);
			break;
			}
		cnt = shmaddr[0]++;//working  with memory
		printf("cnt = %d",cnt); fflush(stdout);
		semop(semid,&v2,1);//for first pross
		}while(1);
		return 0;
}

