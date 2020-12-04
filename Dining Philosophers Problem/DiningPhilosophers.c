#include <stdio.h>

#include <stdlib.h>

#include<time.h>

#include <unistd.h>

#define size 5

struct semaphore_
{
	int data;

}semaphore[5];

int wait(int i)
{

	if(semaphore[i].data <= 0 || semaphore[(i + 1) % size].data <= 0)
	{
		return -1;
	}
	semaphore[i].data--;

	semaphore[(i + 1) % size].data--;

	return 1;
}
int signal(int i)
{
	while(semaphore[i].data > 0 || semaphore[(i + 1) % size].data > 0)
	{
		return -1;
	}
	semaphore[i].data++;

	semaphore[(i + 1) % size].data++;

	return 1;
}
int main()
{
	printf("\n\n Dinning Philosopher Problem \n\n");

	printf("\n Size : %d \n\n" , size);

	for(int i = 0 ; i < size ; i++)
	{
		semaphore[i].data = 1;
	}

	time_t t;

	srand((unsigned)time(&t));

	for(int ph = 0 ; ph < size ; ph++)
	{
		int i = rand() % size;

		if(wait(i) != -1)
		{
		  	printf(" Philosopher %d Picks Up Chopsticks %d and %d \n", i , i , (i + 1) % size);

		  	signal(i);

		  	printf(" Philosopher %d Starts Thinking \n", i);
	  	}
	}
	printf("\n\n The End \n\n");
	return 0;
}