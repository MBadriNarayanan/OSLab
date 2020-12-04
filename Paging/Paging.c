#include <stdbool.h> 

#include <stdio.h>

#include <stdlib.h>

#include<time.h>

#include <unistd.h>

int main()
{
	int no_frames;
	int no_pages;
	int page_size;
	int start_address;
	int address[100];
	int alloc[100];
	int page_address[100];

	printf("\n\n Paging Hardware \n\n");

	printf(" Enter Number Of Frames : ");

	scanf("%d",&no_frames);

	printf(" Enter Number Of Pages : ");

	scanf("%d",&no_pages);

	printf(" Enter Page Size : ");

	scanf("%d",&page_size);

	printf(" Enter Starting Address : ");

	scanf("%d",&start_address);

	printf("\n\n Before Paging \n\n");

	printf(" Frame Number \tPage Number\t\tAddress \n");

	for(int i = 0 ; i < no_frames ; i++)
	{
		alloc[i] = -1;

		printf(" %d\t\t%d\t\t\t%d\n", i , alloc[i] , start_address);

		address[i] = start_address;

		start_address += page_size;
	}

	time_t t;

	srand((unsigned)time(&t));

	printf("\n\n After Paging \n\n");

	printf(" Frame Number \tPage Number\t\tAddress \n");

	bool occupied[100];

	for(int i = 0 ; i < 100 ; i++) 
	{
		occupied[i]  = false;
		page_address[i] = -1;
	}
	for(int i = 0;i<no_pages;i++)
	{
		int r  = rand() % no_frames;

		int counter = 0;

		while(occupied[r % no_frames] == true && counter < no_frames) 
		{
			r = (r + 1) % no_frames;
			counter++;
		}
		if(counter==no_frames)
		{
			alloc[r] = -1;
			page_address[i] = -1;
		}
		else
		{
			alloc[r] = i;
			occupied[r] = true;
			page_address[i] = address[r];
		}
	}
	for(int i = 0; i < no_frames ; i++)
	{
		if (alloc[i] >= 0 )
		{
			printf(" %d\t\t %d\t\t\t%d\n", i , alloc[i] , address[i]);
		}
		else
		{
			printf(" %d\t\t%d\t\t\t%d\n", i , alloc[i] , address[i]);
		}
	}
	int choice = 1;

	while(choice == 1)
	{
		int no;
		int offset;
		printf("\n\n Checking For Trap Error \n\n");
		printf(" Enter Page Number : ");

		scanf("%d",&no);

		printf(" Enter Offset : ");

		scanf("%d",&offset);

		if((page_address[no] + offset >= page_address[no] + page_size)|| page_address[no] == -1)
		{
			printf(" Trap Addressing Error \n\n");
		}
		else
		{
			printf(" Generated Address : %d \n\n" , page_address[no] + offset);
		}
		printf(" Do You Want To Continue (Type 0 or 1) : ");
		scanf("%d",&choice);
	}
	
	printf("\n\n The End \n\n");
	return 0;	
}