#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
int fd;

	if (argc < 2)
		{printf("need file name");return -1;}
	close(0);
	fd = open(argv[1],O_RDONLY);	//читает стантальный поток	
	close(fd);              // ls use "stdout";wc,sort,grep used "stdin"
	execlp("cat","cat",argv[1],NULL);
	return 0;
}

