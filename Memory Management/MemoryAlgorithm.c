#include<stdio.h>
#include<stdlib.h>
typedef     struct
{
        int    *memory;
        int    *process;
        int    no_of_process;
        int    no_of_memory;
        int    max_process;
        int    max_memory;
}Memory; 
Memory*  input(Memory *p)
{
    int i;

        printf("\n\n Input \n\n");

        printf(" Enter Maximum Number of Memories : ");

        scanf("%d",&p->max_memory);

        p->memory=(int*)malloc(p->max_memory*sizeof(int));

        printf(" Enter Maximum Number of Processes : ");

        scanf("%d",&p->max_process);

        p->process=(int*)malloc(p->max_process*sizeof(int));

        printf(" Enter Number of Memories : ");

        scanf("%d",&p->no_of_memory);

        printf(" Enter Number of Processes : ");

        scanf("%d",&p->no_of_process);

        if((p->no_of_process <= p->max_process) && (p->no_of_memory <= p->max_memory))
        {
            printf("\n Memory \n");
            for(int i = 0 ; i < p->no_of_memory ; i++)
            {
                printf("\n Memory %d \n",i + 1);
                printf(" Enter the Memory Value in KB : ");
                scanf("%d",&p->memory[i]);
                printf("\n");
            }
            printf("\n Process \n");
            for(int i = 0 ; i < p->no_of_process ; i++)
            {
                printf("\n Process %d \n",i + 1);
                printf(" Enter the Process Value in KB : ");
                scanf("%d",&p->process[i]);
                printf("\n");
            }
        }
        else if ((p->no_of_process > p->max_process) && (p->no_of_memory > p->max_memory))
        {
            printf(" Memory Size and Process Size Entered Greater than Max Memory Size and Max Process Size");
            return NULL;
        }
        else if (p->no_of_process > p->max_process)
        {
            printf(" Process Size Entered Greater Than Max Process Size \n\n");
            return NULL;
        }
        else if (p->no_of_memory > p->max_memory)
        {
            printf(" Memory Size Entered Greater Than Max Memory Size \n\n");
            return NULL;
        }
}
int display_memory(Memory *p)
{
    int i;
        
        printf("\n\n Display Memory\n\n");
        if (p->no_of_memory > p->max_memory)
        {
            printf(" Memory Size Entered Greater Than Max Memory Size \n\n");
            return 0;
        }
        else
        {
            for(i = 0;i<p->no_of_memory;i++)
            {
                printf(" Memory[%d] = %d \n",i + 1 , p->memory[i]);
            }
            printf("\n\n");
            return 1;
        }
}
int display_process(Memory *p)
{
    int i;
        
        printf("\n\n Display Process\n\n");
        if (p->no_of_process > p->max_process)
        {
            printf(" Process Size Entered Greater Than Max Process Size \n\n");
            return 0;
        }
        else
        {
            for(i = 0;i<p->no_of_process;i++)
            {
                printf(" Process[%d] = %d \n",i + 1 , p->process[i]);
            }
            printf("\n\n");
            return 1;
        }
}
Memory* firstfit(Memory *p)
{
    printf("\n\n First Fit Algorithm Started \n\n");
    for(int l = 0; l < p->no_of_process ; l++)
    {
        int max = 0;
        for(int k = 0; k < p->no_of_memory ; k++)
        {
            if(p->memory[k]>= p->process[l])
            {
                max = p->memory[k];
                p->memory[k]-= p->process[l];
                break;
            }
        }
        if(max>0)
        {
            printf(" %d KB is put in %d KB\n",p->process[l],max);
        }
        else
        {  
            printf(" %d KB must wait\n",p->process[l]);
        }
    }
    printf("\n\n First Fit Algorithm Ends \n\n");
    display_memory(p);
    return p;
}
Memory* bestfit(Memory *p)
{
    printf("\n\n Best Fit Algorithm Started \n\n");
    for(int l = 0; l < p->no_of_process; l++)
    {
        int ar[p->no_of_memory];
        int min = 10000;
        int a;
        for(int k = 0; k < p->no_of_memory; k++)
        {
            ar[k]= p->memory[k]- p->process[l];
        }
        for(int h = 0; h < p->no_of_memory ; h++)
        {
            if(ar[h] < min && ar[h] > -1)
            {
                min = ar[h];
                a = h;
            }
        }
        if(p->memory[a] >= p->process[l])
        {
            printf(" %d KB is put in %d KB\n",p->process[l],p->memory[a]);
            p->memory[a]-=p->process[l];
        }
        else
        {   
            printf(" %d must wait\n",p->process[l]);
        }
    }
    printf("\n\n Best Fit Algorithm Ends \n\n");
    display_memory(p);
    return p;
}
Memory* worstfit(Memory *p)
{
    printf("\n\n Worst Fit Algorithm Started \n\n");
    for(int l = 0; l < p->no_of_process ; l++)
    {
        int a;
        int max = p->memory[0];
        for(int k=1; k < p->no_of_memory; k++)
        {
            if(p->memory[k]>max)
            {
                max = p->memory[k];
                a = k;
            }
        }
        if(p->memory[a] >= p->process[l])
        {
            printf(" %d KB is put in %d KB\n",p->process[l],p->memory[a]);
            p->memory[a]-= p->process[l];
        }
        else
        {
            printf(" %d must wait \n",p->process[l]);
        }
    }
    printf("\n\n Worst Fit Algorithm Ends \n\n");
    display_memory(p);
    return p;
}
int main()
{
    int     choice;
            do
            {
                printf("\n\n Memory Management Algorithms \n\n");
                printf(" 1) First Fit Algorithm \n");
                printf(" 2) Best Fit Algorithm \n");
                printf(" 3) Worst Fit Algorithm \n");
                printf(" 4) Exit \n");
                printf(" Enter your choice : ");
                scanf("%d", &choice);
                switch (choice)
                {
                        
                    case 1 :
                            {
                                Memory  p;
                                Memory  *t;
                                t = input(&p);
                                display_memory(&p);
                                display_process(&p);
                                t = firstfit(&p);
                                break;
                            }
                    case 2 :
                            {
                                Memory  p;
                                Memory  *t;
                                t = input(&p);
                                display_memory(&p);
                                display_process(&p);
                                t = bestfit(&p);
                                break;
                            }
                    case 3 :
                            {
                                Memory  p;
                                Memory  *t;
                                t = input(&p);
                                display_memory(&p);
                                display_process(&p);
                                t = worstfit(&p);
                                break;
                            }
                    default :
                            {
                                printf("\n\n Exit.......\n\n");
                                break;
                            }
                }
                printf("\n Do you want to continue (Type 0 or 1) : ");
                scanf("%d",&choice);
            }while (choice);
            printf("\n\n The End \n\n");
            return 0;
}