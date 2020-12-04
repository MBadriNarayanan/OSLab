#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int pid;
    int start;
    int arr;
    int burst;
    int pri;
    int rem;
    int wait;
    int turn;
    int flag;
}Process;


void input(Process p[] , int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("\n Process %d \n",i + 1);
        printf(" Enter the Arrival Time : ");
        scanf("%d", &p[i].arr);
        printf(" Enter the Burst Time : ");
        scanf("%d", &p[i].burst);
        printf(" Enter the Priority : ");
        scanf("%d",&p[i].pri);
        p[i].pid = i + 1;
        p[i].flag = 0;
        p[i].rem = p[i].burst;
        printf("\n");
    }
    printf("\n\n");
}

void gantt(Process arr[], int n, int tot_time)
{
    if(n <= 0)
    {
        return;
    }
    
    printf("\n\n\t GANTT CHART \n\n");
    
    int i, j;

    printf("\n\n+");

    for (i = 0; i < n - 1; i++)
    {
        for (j = arr[i].start; j < arr[i + 1].start; j++)
        {
            printf("--");
        }
        printf("+");
    }

    for (j = 0; j < tot_time - arr[n - 1].start; j++)
    {
        printf("--");
    }
    printf("+");

    printf("\n|");

    for (i = 0; i < n - 1; i++)
    {
        for (j = arr[i].start; j < arr[i + 1].start - 1; j++)
        {
            printf(" ");
        }
        printf("P%d", arr[i].pid);

        for (j = arr[i].start; j < arr[i + 1].start - 1; j++)
        {
            printf(" ");
        }
        printf("|");
    }

    for (j = 0; j < tot_time - arr[n - 1].start - 1; j++)
    {
        printf(" ");
    }
    printf("P%d", arr[n - 1].pid);
    for (j = 0; j < tot_time - arr[n - 1].start - 1; j++)
    {
        printf(" ");
    }
    printf("|");

    printf("\n+");

    for (i = 0; i < n - 1; i++)
    {
        for (j = arr[i].start; j < arr[i + 1].start; j++)
        {
            printf("--");
        }
        printf("+");
    }

    for (j = 0; j < tot_time - arr[n - 1].start; j++)
    {
        printf("--");
    }
    printf("+");

    printf("\n");


    for (i = 0; i < n - 1; i++)
    {
        printf("%d", (int)arr[i].start);
        for (j = arr[i].start; j < arr[i + 1].start; j++)
        {
            printf("  ");
        }
        if (arr[i].start > 9)
        {
            printf("\b"); 
        }
    }

    printf("%d", (int)arr[n - 1].start);
    for (j = 0; j < tot_time - arr[n - 1].start; j++)
    {
        printf("  ");
    }

    if (tot_time > 9)
    {
        printf("\b%d", tot_time); 
    }
    printf("\n\n");

}

void display(Process ar[],int n)
{
    float avgturn = 0;

    float avgwait = 0;

    Process temp;

    for(int i = 0 ; i < n - 1 ; i++)
    {
        for(int j = i + 1 ; j < n ; j++)
        {
            if(ar[j].pid < ar[i].pid)
            {
                temp = ar[j];
                ar[j] = ar[i];
                ar[i] = temp;
            }
        
        }
    }
    
    printf("-----------------------------------------------------------------------------------------------------------------"); 
    printf("\n|\t ProcessId \t|\tArrival \t|\tBurst \t\t|\t Turnaround \t|\tWaiting |\n");    
    printf("-----------------------------------------------------------------------------------------------------------------");
    for(int i = 0; i < n; i++)
    {
        printf("\n|\t P%d \t\t|\t %d \t\t|\t %d \t\t|\t %d \t\t|\t %d  \t|\n",ar[i].pid, ar[i].arr, ar[i].burst, ar[i].turn, ar[i].wait);

        avgturn += ar[i].turn;

        avgwait += ar[i].wait;

    }
    printf("-----------------------------------------------------------------------------------------------------------------\n");
 
    printf("|\t\t\t\t\t\t\t\t\t| \t\t\t|\t\t|\n| Average \t\t\t\t\t\t\t\t|\t%.2f\t\t|\t%.2f\t|",avgturn/n,avgwait/n);
    printf("\n-----------------------------------------------------------------------------------------------------------------\n");
    printf("\n");

}

void rr(Process ar[] , int n)
{
    int time = 0;

    float avgturn = 0;

    float avgwait = 0;

    int prev = -1;

    time = 0;

    int remain = 0;

    int endtime;

    int q;

    printf(" Enter The Time Quantum : ");

    scanf("%d",&q);

    int t = 0;

    int i = 0;

    Process temp;

    Process g[10];

    int count = 0;
    
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(ar[j].arr<ar[i].arr)
            {
                temp=ar[j];
                ar[j]=ar[i];
                ar[i]=temp;
            }
        }
    }
    
    for(int i=0;i<n;i++)
    {
        time+=ar[i].burst;
    }
    
    while(remain!=n)
    {
        if(ar[i].flag==0)
        {
        
            if(ar[i].rem>q && ar[i].flag==0)
            {
                ar[i].start=t;
                g[count++]=ar[i];
                t=t+q;
                ar[i].rem-=q;
            }
            else if(ar[i].flag==0)
            {
                ar[i].start=t;
                g[count++]=ar[i];
                t=t+ar[i].rem;
                ar[i].rem=0;
            }
            if(ar[i].rem==0)
            {
                remain++;
                endtime=t;
                ar[i].turn=endtime-ar[i].arr;
                ar[i].wait=endtime-ar[i].burst-ar[i].arr;
                ar[i].flag=1;
            }
            i = (i + 1) % n;
        }
        else
        {
            i = (i + 1) % n;
        }
    }
    display(ar,n);
    gantt(g,count,time);
}

int main()
{
    int n;
    int choice;
    do
    {
        Process ar[10];
        printf("\n\n Round Robin Scheduling \n\n");
        printf(" Enter the number of processes : ");
        scanf("%d", &n);
        input(ar,n);
        rr(ar,n);
        printf("\n Do you want to continue (Type 0 or 1) : ");
        scanf("%d",&choice);
    }while (choice);
    printf("\n\n The End \n\n");
    return 0;
}