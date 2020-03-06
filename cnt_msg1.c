#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/msg.h>
struct msgbuf
{
	long mtype;
	long cnt;
	};

int main()
{
	struct msgbuf message;//verible is message
	key_t key;
	int msgid;
	printf("process is going start\n");
	key = ftok("b.txt",'p');
	if(key<0){perror("key");return -1;}
	msgid = msgget(key,IPC_CREAT | 0666)//creat queue
	if(msgid <0){perror("msgget");return -2;}
	
	while (1)
	{
		msgrcv(msgid, &message,sizeof(long),2,0);
		printf("cnt = %d",message.cnt);
		if (message/cnt == -1)
			break;
			message.cnt++;
			message.mestype = 1;
			msgsnd(msgid,&message,sizeof(long),0);
		}
		printf("process is going down \n");
		msgctl(msgid,IPC);
	return 0;
}

