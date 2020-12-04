#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int     pid;
    float   at, bt, st, et, wt, tat, rt, rem_t, pri;
} Process;

#include "MinHeap.h"

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
    for (i = 0; i < n - 1; i++)
    {
        printf("%d", (int)arr[i].st);
        for (j = arr[i].st; j < arr[i + 1].st; j++)
        {
            printf("  ");
        }
        if (arr[i].st > 9)
        {
            printf("\b"); 
        }
    }

    printf("%d", (int)arr[n - 1].st);
    for (j = 0; j < tot_time - arr[n - 1].st; j++)
    {
        printf("  ");
    }

    if (tot_time > 9)
    {
        printf("\b%d", tot_time); 
    }
    printf("\n\n");
}

void SJF(Process *const p, const int size)
{
    int     completed = 0;
    int     last_process = 0;
    int     index = 0;
    int     prev_id = -1;
    float   tot_tat = 0;
    float   tot_wt = 0;
    int     count = 0;
    Process gantt[20];
    Process tmp;
    PQueue processQueue = createPQueue(size);
    int time = 0;

    int total_time = 0;
    for (int i = 0; i < size; i++)
    {
        total_time += p[i].bt;
    }

    while (completed != size)
    {
        for (int i = last_process; i < size; ++i)
        {
            if (p[i].at <= time)
            {
                enqueue(processQueue, p[i]);
                last_process = i + 1;
            }
        }
        tmp = dequeue(processQueue);
        index = getIndex(p, size, tmp);

        if (tmp.rem_t == -1)
        {
            time++;
            continue;
        }

        p[index].st = time;
        p[index].rt = p[index].st - p[index].at;
        p[index].et = time + p[index].bt;
        p[index].tat = p[index].et - p[index].at;
        tot_tat += p[index].tat;
        p[index].wt = p[index].tat - p[index].bt;
        tot_wt += p[index].wt;
        completed++;
        time += p[index].bt;
        gantt[count++] = p[index];
    }

    gantt_chart(gantt, count, time);

    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    printf("| PID | Arrival Time | Burst Time | Start | End  | Wait Time | TAT  |\n");
    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    for (int i = 0; i < size; i++)
    {
        printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].et, p[i].wt, p[i].tat);
    }
    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    printf("|                                 | Total        | %-9.1f | %-4.1f |\n", tot_wt, tot_tat);
    printf("|                                 | Average      | %-9.1f | %-4.1f |\n", tot_wt / size, tot_tat / size);
    printf("+-----+--------------+------------+-------+------+-----------+------+\n\n");
}

void SRTF(Process *const p, const int size)
{
    int completed = 0;
    int last_process = 0;
    int index = 0;
    int prev_id = -1;
    float tot_tat = 0;
    float tot_wt = 0;
    int time = 0;
    int count = 0;
    int total_time = 0;

    Process tmp;
    PQueue processQueue = createPQueue(size);
    Process gantt[20];

    for (int i = 0; i < size; i++)
    {
        total_time += p[i].bt;
    }

    while (completed < size)
    {
        for (int i = last_process; i < size; ++i)
        {

            if (p[i].at == time)
            {
                enqueue(processQueue, p[i]);
                last_process = i + 1;
            }
        }
        tmp = dequeue(processQueue);
        if (tmp.rem_t == -1)
        {
            printf("| -  ");
            time++;
            continue;
        }
        index = getIndex(p, size, tmp);

        if (p[index].st == -1)
        { 
            p[index].st = time;
            p[index].rt = p[index].st - p[index].at;
            gantt[count++] = p[index];
        }
        tmp.rem_t--;
        p[index].rem_t--;
        if (p[index].pid != gantt[count - 1].pid)
        {
            gantt[count++] = p[index];
            gantt[count - 1].st = time;
        }
        if (tmp.rem_t == 0)
        {
            p[index].et = time + 1;
            p[index].tat = p[index].et - p[index].at;
            tot_tat += p[index].tat;
            p[index].wt = p[index].tat - p[index].bt;
            tot_wt += p[index].wt;
            completed++;
        }
        else
        {
            enqueue(processQueue, p[index]);
        }
        time++;
    }
    gantt_chart(gantt, count, total_time);

    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    printf("| PID | Arrival Time | Burst Time | Start | End  | Wait Time | TAT  |\n");
    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    for (int i = 0; i < size; i++)
    {
        printf("| %3d | %-12.1f | %-10.1f | %-5.1f | %-4.1f | %-9.1f | %-4.1f |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].et, p[i].wt, p[i].tat);
    }
    printf("+-----+--------------+------------+-------+------+-----------+------+\n");
    printf("|                                 | Total        | %-9.1f | %-4.1f |\n", tot_wt, tot_tat);
    printf("|                                 | Average      | %-9.1f | %-4.1f |\n", tot_wt / size, tot_tat / size);
    printf("+-----+--------------+------------+-------+------+-----------+------+\n\n");
}
int main()
{
    int size;
    int choice = 5;
    do
    {
        printf("\n\n SJF Scheduling \n\n");
        printf(" 1) Non Preemptive\n");
        printf(" 2) Preemptive \n");
        printf(" 3) Exit \n");
        printf(" Enter your choice : ");
        scanf("%d", &choice);
    
        switch (choice)
        {
                
            case 1 :
                    {
                        printf("\n\n Non Preemptive \n\n");
                        printf(" Enter the number of processes : ");
                        scanf("%d", &size);
                        printf("\n");
                        Process *p = getProcesses(size);
                        SJF(p, size);
                        break;
                    }
            case 2 :
                    {
    
                        printf("\n\n Preemptive \n\n");
                        printf(" Enter the number of processes : ");
                        scanf("%d", &size);
                        printf("\n");
                        Process *p = getProcesses(size);
                        SRTF(p, size);
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