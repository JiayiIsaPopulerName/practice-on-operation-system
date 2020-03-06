#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <unistd.h>

struct msgbuf
{
		long mtype;
		char data[256];
}message;

int main()
{
	key_t key;
	int msgid,x = 1;
	char *s = "  Send  : ";
	char str[256];

	key = ftok("c.txt", 'r');
	if (msgid < 0)
	{
		perror("msgget");
		return -1;
	}
	msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid < 0)
	{
		perror("msgget");
		return -1;
	}
	for(;;)
	{
		write(1, s, 10);
		fgets(str, 255, stdin);
		message.mtype = 1;
		strcpy(message.data, str);
		if ((strlen(str) == 1) && (str[0] == 'q'))
		{
			msgsnd(msgid, &message, 1, 0);
			
			msgctl(msgid, IPC_RMID, NULL);
			return 0;
		}
		msgsnd(msgid, &message, strlen(str)+1, 0);
		msgrcv(msgid, &message, 256, 2, 0);
		if ((strlen(message.data) == 2) && (message.data[0] == 'q'))
		{
			msgctl(msgid, IPC_RMID, NULL);
			return 0;
		}
		printf("Receive : %s", message.data);
	}
}
