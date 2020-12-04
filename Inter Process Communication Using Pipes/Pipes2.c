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
	int fd2[2];
	char msg[4] = {'M','B','N','\0'};
	char msg1[4];
	char msg2[4];

	if(pipe(fd1) == -1)
	{
		printf("\n\n Pipe ' Pipe 1 ' Creation Unsuccessful \n\n");
	}
	else
	{
		printf("\n\n Pipe ' Pipe 1 ' Creation Successful \n\n");
	}

	if(pipe(fd2)==-1)
	{
		printf("\n\n Pipe ' Pipe 2 ' Creation Unsuccessful \n\n");
	}
	else
	{
		printf("\n\n Pipe ' Pipe 2 ' Creation Successful \n\n");
	}

	pid = fork();

	if(pid > 0)
	{
		wait(0);

		printf("\n\n Parent Process \n\n");

		printf("\n\n Reading From Pipe 1 and Writing It Into Pipe 2 \n\n");

		close(fd1[1]);

		read(fd1[0] , msg1 , sizeof(msg1));

		write(fd2[1] , msg1 , sizeof(msg1));

		int pid2 = fork();

		if(pid2 == 0)
		{
			printf("\n\n Child Process II \n\n");

			close(fd2[1]);

			read(fd2[0], msg2, sizeof(msg2));

			printf("\n\n Message From Parent Is : %s \n\n" , msg2);
		}
	}
	else
	{
		printf("\n\n Child Process I \n\n");

		close(fd1[0]);

		write(fd1[1] , msg , sizeof(msg));

	}
	printf("\n\n The End \n\n");
	return 0;
}	