#include <stdio.h>
#include <signal.h>

void sighandler(int s)
{
	static int count = 0;
	signal(SIGUSR1,sighandler);
	count++;
	printf("%d\n",count);
	}
int main()
{	
	signal(SIGUSR1,sighandler);
	while(1);
	return 0;
}

