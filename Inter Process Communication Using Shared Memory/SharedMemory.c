#include<stdio.h>

#include<sys/ipc.h>

#include<unistd.h>

#include<sys/types.h>

#include<sys/shm.h>

#include<sys/wait.h>

#include<string.h>

int main()
{
	printf(" \n\n Inter Process Communication Using Shared Memory \n\n");

	int r = fork();
	
	if(r!=0)
	{
		wait(0);

		printf("\n\n Client Process \n\n");

		key_t key = ftok("shmfile", 65);

		int shmid = shmget(key, 1024 , 0666|IPC_CREAT);

		char *str1 = (char*) shmat(shmid , (void*)0 , 0);

		printf("\n\n Data Read From Shared Memory : %s \n",str1);
		
		shmdt(str1);

	}
	else
	{
		printf("\n\n Server Process \n\n");

		key_t key = ftok("shmfile",65);

		int shmid = shmget(key , 1024 , 0666|IPC_CREAT);

		char *str = (char*) shmat(shmid, (void*)0 ,0);

		printf(" Enter Data To Be Written To Be In Shared Memory : ");

		gets(str);

		shmdt(str);
	}
	printf("\n\n The End \n\n");
	return 0;
}
