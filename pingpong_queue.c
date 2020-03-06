#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>

#define CNT_MAX 10

int main()
{
	key_t key;
	int semid,shmid;
	struct sembuf v1 = {0,1,0};
	struct sembuf p2 = {1,-1,0};
	
	int *shmaddr;
	int cnt = 0;
	
	key = ftok("a.txt",'t');
	if (key < 0){perror("ftok");exit(-1);}
	shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);
	if (shmid <0 ){perror("shmid");exit(-1);}
	semid = semget(key,2,0666 | IPC_CREAT);
	if (semid < 0){perror("semget");return -1;}
	
	semctl(semid, 0, SETVAL, 0);
	
	shmaddr = shmat(shmid,NULL,0);
	if (shmaddr == (void*)-1){perror("shmaddr");return -1;}
	
	*shmaddr = 0;
	
	while (cnt < CNT_MAX)
	{
		cnt = (*shmaddr)++;
		semop(semid,&v1,1);//for second pross
		
		printf("cnt = %d",cnt); fflush(stdout);
		semop(semid,&p2,1);
	}
	*shmaddr = -1;
	semop(semid, &v1,1);
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, 0, IPC_RMID, 0);
	return 0;

}

