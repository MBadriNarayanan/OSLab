#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <unistd.h>
#define buffer_size 3

int main()
{
	printf("\n\n Bounded Buffer Problem \n\n");

	int r ;

	int buffer[buffer_size] ;

	int counter = 0 ;

	int in = 0 ;

	int out = 0 ;

	time_t t ;

	srand((unsigned)time(&t)) ;

	for(int i = 0 ; i < 20 ; i++)
	{
		int r = rand() % 1000 + 1 ;
		if(r % 2 == 0)
		{
			if(counter == buffer_size)
			{
				printf(" Buffer Full \n\n");

				continue;
			}
			buffer[in] = r ;

			printf(" Item %d Produced By Producer \n\n", in % buffer_size + 1);

			in = (in + 1 ) % buffer_size;

			counter = counter + 1;
		}
		else
		{
			if(counter == 0)
			{
				printf(" Buffer Empty \n\n");

				continue;
			}

			buffer[out] = 0 ; 

			printf(" Item %d Consumed By Consumer \n\n", out % buffer_size + 1);

			out = (out + 1) % buffer_size;

			counter = counter - 1;

		}
	}

	printf("\n\n The End \n\n");

	return 0;
}