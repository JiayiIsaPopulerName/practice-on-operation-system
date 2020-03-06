#include<stdio.h>
#include<stdlib.h>
int main()
{
	unsigned short num;
	unsigned short  mask=1;
	int n=9;
	int i=0,j=0;
	char str[9]="rwxrwxrwx";
	char array[8];
	
	scanf("%ho",&num);
	for (mask<<=n-1; mask; mask>>=1 )
	{
	if (mask&num) 
	{	
		printf("1");
                	array[i++]='1';}
		else {
			printf("0");
			array[i++]='0';
	
	}
	}
	printf("\n");
	for (i=0; i<9; i++)
	{
	if (array[i]=='1')
			printf("%c",str[j++]);
	else{ 
		printf("-");
		j++;
	}
	}	
	
	printf("\n");
	return 0;
}
