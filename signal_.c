#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
	static int count1 = 0;
void sig_quit(int s)
{
	static int count = 0;
	
	if(s == SIGQUIT)//control |
	{
		count++;
		printf("recieved SIGQUIT %d times\n",count);
			
		}
}		
void sig_int(int a)
{
	if(a == SIGINT)
		if(count1 == 7)
			exit(0);
		if((count1 > 2)||(count1 < 4))	
		{
			count1++;
			printf("recieved SIGINT %d times\n",count1);
		}
}

int main()
{
	pid_t pid=getpid();
	while (count1 < 7)
	{
		if((count1 > 2)||(count1 < 4)){
			signal(SIGINT,sig_quit);}
			
		signal(SIGQUIT,sig_int);
	}
		kill(pid,SIGINT);
		kill(pid,SIGQUIT);
	
	return 0;
}

