#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv )
{
int fd[2],ff,n;
pid_t pid;
char *arg[] = {"ls","-l", NULL};
char buf[256];

	if (argc<2)
	{
		fprintf(stderr,"need filename\n");
		return -1;
	}
	
	if(pipe(fd)< 0){perror("pipe");return -1;}
	pid =fork();
	if (pid< 0){perror("fork");return -1;}
	else if (pid == 0)
	{
		dup2(fd[1],1);
		close(fd[0]);close(fd[1]);
		execvp("ls",arg);
		perror("exec");
		return -2;
	}
	ff = creat(argv[1],0644);
	if (ff < 0){perror("open");return -4;}
	close(fd[1]);
	
	while((n = read(fd[0],buf, 256)) > 0)
		write(ff,buf,n);
	close(fd[1]);
	close(ff);
return 0;
}



