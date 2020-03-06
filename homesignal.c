#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int c = 0,count = 1;
char *str = "I've got SIGINT";

void Sign(int s)
{
	if (s ==SIGINT)
	{
			//count++;
		write(1, str ,16);
		printf(" This is %d times(s)\n",count);	
		if (count == 7)
			exit(0);
		if (count > 3)
			printf("Received %d SIGQUIT\n",c);
		count++;
	}
}

void Quit(int z)
{
	if (z == SIGQUIT)
	{
		c++;
		printf("Received %d SIGQUIT\n",c);
	}
}

int main()
{	
	pid_t pid = getpid();
	while (count < 7)
	{
		signal(SIGINT, Sign);
		while ((count >= 2) && (count <= 3))
		{	
			signal(SIGQUIT, Quit);
			signal(SIGINT, Sign);
		}
	}
	kill(pid,SIGINT);
	kill(pid,SIGQUIT);
	return 0;
}
