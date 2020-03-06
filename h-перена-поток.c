#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	int fd;
	
	if(argc < 2)
	{
		printf("need file");
		return -1;
		}
		
		fd = open(argv[1],O_RDONLY);
		close(0);
		dup(fd);
		execlp("cat","cat",argv[1],NULL);
	
	return 0;
}

