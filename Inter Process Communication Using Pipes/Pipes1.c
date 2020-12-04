#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include<sys/time.h>

int main()
{
	printf("\n\n Inter Process Communication Using Pipes \n\n");

	int fd1[2];
	int pid;
	char msg[4] = {'M','B','N','\0'};
	char msg1[4];

	if(pipe(fd1) == -1)
	{
		printf("\n\n Pipe ' Pipe 1 ' Creation Unsuccessful \n\n");
	}
	else
	{
		printf("\n\n Pipe ' Pipe 1 ' Creation Successful \n\n");
	}

	pid = fork();

	if(pid > 0)
	{
		wait(0);

		printf("\n\n Parent Process \n\n");

		printf("\n\n Reading From Pipe 1 \n\n");

		close(fd1[1]);

		read(fd1[0], msg1, sizeof(msg1));

		close(fd1[0]);

		printf("\n\n Message From Child :  %s \n\n",msg1);
	}
	else
	{
		printf("\n\n Child Process \n\n");

		printf("\n\n Child Process Writing Into Pipe \n\n");

		close(fd1[0]);

		write(fd1[1],msg,sizeof(msg));

	}
	printf("\n\n The End \n\n");
	return 0;
}	
