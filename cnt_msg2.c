#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msbuf
{
	long mestype;
	long cnt;
};

int main()
{
	struct msbuf message;
	key_t key;
	int msgid;

	printf("process is going start\n");
	key = ftok("a.txt", 'p');
	if (key < 0)
	{
		perror("ftok");
		return -1;
	}
	msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid < 0)
	{
		perror("msgget");
		return -1;
	}

	while(1)
	{
		msgrcv(msgid, &message, sizeof(long), 2, 0);
		printf("cnt = %ld\n", message.cnt);
		if (message.cnt == -1)
			break;
		message.cnt++;
		message.mestype = 1;
		msgsnd(msgid, &message, sizeof(long), 0);
	}
	printf("process is going down\n");
	msgctl(msgid, IPC_RMID, 0);
	return 0;
}
