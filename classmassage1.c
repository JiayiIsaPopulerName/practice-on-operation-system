#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define CNT_MAX 10

struct msgbuf
{
	long mestype;
	long cnt;
};

int main()
{
	struct msgbuf message;
	key_t key;
	int msgid;
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

	printf("process is going start\n");

	message.mestype = 2;
	message.cnt = 1;
	msgsnd(msgid, &message, sizeof(long), 0);

	while (1)
	{
		msgrcv(msgid, &message, sizeof(long), 1, 0);
		printf(" cnt = %ld\n", message.cnt);
		if (message.cnt < CNT_MAX)
		{
			message.mestype = 2;
			message.cnt++;
			msgsnd(msgid, &message, sizeof(long), 0);
		}
		else
		{
			message.mestype = 2;
			message.cnt = -1;
			msgsnd(msgid, &message, sizeof(long), 0);
			printf("process is going down\n");
			break;
		}
	}
	return 0;
}
			
