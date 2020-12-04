#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int 	pid;
    float 	at, bt, st, et, wt, tat, rt, rem_t, pri;
} Process;


int getIndex(Process *const arr, const int size, const Process p)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].pid == p.pid)
        {
            return i;
        }
    }

    return -1;
}

Process *getProcesses(const int size)
{
    static Process p[100];

    for (int i = 0; i < size; i++)
    {
        printf("\n Process %d \n",i + 1);
        printf(" Enter the Arrival Time : ");
        scanf("%f", &p[i].at);
        printf(" Enter the Burst Time : ");
        scanf("%f", &p[i].bt);
        printf(" Enter the Priority : ");
        scanf("%f",&p[i].pri);
        getchar();
        p[i].pid = i + 1;
        p[i].rt = -1;
        p[i].rem_t = p[i].bt;
        p[i].st = p[i].et = -1;
        p[i].wt = p[i].tat = -1;
        printf("\n");
    }

    return p;
}

void gantt_chart(Process arr[], int n, int tot_time)
{
    if (n <= 0)
        return;

    printf("\n\n GANTT CHART \n\n");

    int i, j;

    // printing the top bar
    printf("\n\n+");
    for (i = 0; i < n - 1; i++)
    {
        for (j = arr[i].st; j < arr[i + 1].st; j++)
        {
            printf("--");
        }
        printf("+");
    }

    for (j = 0; j < tot_time - arr[n - 1].st; j++)
    {
        printf("--");
    }
    printf("+");

    printf("\n|");

    // printing the process id in the middle
    for (i = 0; i < n - 1; i++)
    {
        for (j = arr[i].st; j < arr[i + 1].st - 1; j++)
        {
            printf(" ");
        }
        printf("P%d", arr[i].pid);

        for (j = arr[i].st; j < arr[i + 1].st - 1; j++)
        {
            printf(" ");
        }
        printf("|");
    }

    for (j = 0; j < tot_time - arr[n - 1].st - 1; j++)
    {
        printf(" ");
    }
    printf("P%d", arr[n - 1].pid);
    for (j = 0; j < tot_time - arr[n - 1].st - 1; j++)
    {
        printf(" ");
    }
    printf("|");

    printf("\n+");

    // printing the bottom bar
    for (i = 0; i < n - 1; i++)
    {
        for (j = arr[i].st; j < arr[i + 1].st; j++)
        {
            printf("--");
        }
        printf("+");
    }

    for (j = 0; j < tot_time - arr[n - 1].st; j++)
    {
        printf("--");
    }
    printf("+");

    printf("\n");

    // printing the time line
    for (i = 0; i < n - 1; i++)
    {
        printf("%d", (int)arr[i].st);
        for (j = arr[i].st; j < arr[i + 1].st; j++)
        {
            printf("  ");
        }
        if (arr[i].st > 9)
        {
            printf("\b"); // backspace : remove 1 space
        }
    }

    printf("%d", (int)arr[n - 1].st);
    for (j = 0; j < tot_time - arr[n - 1].st; j++)
    {
        printf("  ");
    }

    if (tot_time > 9)
    {
        printf("\b%d", tot_time); // backspace : remove space for two digit time instances
    }
    printf("\n\n");
}

void FCFS(Process *const arr, const int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j].at < arr[i].at) //Arrived Earlier
            {
                Process tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
    Process gantt[20];
    int 	count = 0;
    int 	time = 0;
    int 	total_time = 0;
    float 	tot_wt = 0;
    float 	tot_tat = 0;
    for (int i = 0; i < size; i++)
    {
        arr[i].st = time;
        arr[i].et = arr[i].st + arr[i].bt;
        arr[i].wt = arr[i].st - arr[i].at;
        arr[i].rt = arr[i].wt;
        arr[i].tat = arr[i].et - arr[i].at;
        gantt[count++] = arr[i];
        time +=arr[i].bt;
        total_time	+=arr[i].bt;
        tot_wt += arr[i].wt;
        tot_tat += arr[i].tat;
    }

    gantt_chart(arr,size,total_time);
    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    printf("| PID | Arrival Time | Burst Time | Start | End  | Wait Time | TAT  |\n");
    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    for (int i = 0; i < size; i++)
    {
        printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f |\n",
               arr[i].pid, arr[i].at, arr[i].bt, arr[i].st, arr[i].et, arr[i].wt, arr[i].tat);
    }
    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    printf("|                                 | Total        | %-9.1f | %-4.1f |\n", tot_wt, tot_tat);
    printf("|                                 | Average      | %-9.1f | %-4.1f |\n", tot_wt / size, tot_tat / size);
    printf("+-----+--------------+------------+-------+------+-----------+------+\n\n");

}
int main(void)
{
    int size;
    int quantum;
    int choice = 5;
    do
    {
        printf("\n\n FCFS Scheduling \n\n");
        printf(" Enter the number of processes : ");
        scanf("%d", &size);
        Process *p = getProcesses(size);
        FCFS(p, size);
        printf("\n Do you want to continue (Type 0 or 1) : ");
        scanf("%d",&choice);
    }while (choice);
    printf("\n\n The End \n\n");
    return 0;
}
        