#include <stdio.h>

int size =  (int)4;

int max(int i , int j)
{
	if(i>j)
	{
		return i;
	}
	return j;
}
int search(int a[] , int n , int s)
{
	for(int i = 0;i<n;i++)
	{
		if(a[i]==s)
		{
			return i;
		}
	}
	return -1;
}
int main()
{
	printf("\n\n Page Replacement Technique LRU \n\n");

	int n;

	int a[100];

	printf(" Enter Number Of Frames : ");

	scanf("%d",&size);

	printf(" Enter Length Of Page Reference String : ");

	scanf("%d",&n);

	printf("\n\n Page Reference String Input \n\n");

	for(int i = 0; i < n ; i++)
	{
		printf(" Enter Value %d : ", i + 1);
		scanf("%d",&a[i]);
		printf("\n");
	}
	
	int frame[100];

	int temp[100];

	for(int i = 0; i < size ; i++)
	{
		frame[i] = temp[i] = 0;
	}

	int fault = 0;

	for(int i = 0; i < n ; i++)
	{
		for(int j = 0; j < size ; j++) 
		{
			temp[j] = 0;
		}
		printf("\n\n Inserting : %d \n\n",a[i]);

		if(search(frame,size,a[i])==-1)
		{
			printf("\n\n FAULT \n\n");

			fault++;

			for(int j = i - 1 ; j >= max(0 , i-(size-1)); j--)
			{
				if(search(frame, size , a[j]) != -1)
				{
					temp[search(frame , size , a[j])] = 1;
				}
			
			}
			for(int j = 0 ; j < size ; j++) 
			{
			  	if(temp[j] == 0)
			  	{
				 	frame[j] = a[i];

				 	break;
			  	}
			}
		}
		for(int i = 0 ; i < size ; i++)
		{
			printf(" Frame Number %d : %d \n", i + 1 ,frame[i]);
		}
		printf("\n");
	}	
	printf("\n\n Number Of Faults : %d \n\n", fault);
	printf("\n\n The End \n\n");
	return 0;
}