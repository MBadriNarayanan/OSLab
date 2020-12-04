#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int     pid, pri;
    float   at, bt;
    float   st, et;
    float   wt, tat;
    float   rt, rem_t;
} Process;

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
        scanf("%d",&p[i].pri);
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

void priority_np(Process arr[], const int size)
{
    int     time = 0;
    float   avgturn = 0;
    float   avgwait = 0;
    int     min;
    int     index;
    Process gantt[20];
    int     count = 0;
    float   tot_tat = 0;
    float   tot_wt = 0;

    time = 0;
    for (int i = 0; i < size; i++)
    {
        time += arr[i].bt;
    }

    for (int t = 0; t < time;)
    {
        min = 9999;
        for (int i = 0; i < size; i++)
        {
            if (arr[i].at <= t && arr[i].pri < min && arr[i].rem_t)
            {
                min = arr[i].pri;
                index = i;
            }
        }

        arr[index].rem_t = 0;
        arr[index].wt = t - arr[index].at;
        arr[index].st = t;
        arr[index].rt = arr[index].st - arr[index].at;
        t += arr[index].bt;
        arr[index].et = t;
        arr[index].tat = arr[index].et - arr[index].at;
        tot_tat += arr[index].tat;
        tot_wt += arr[index].wt;
        gantt[count++] = arr[index];
    }

    gantt_chart(gantt, size, time);

    printf("+-----+--------------+------------+-----+-------+------+-----------+------+\n");
    printf("| PID | Arrival Time | Burst Time | PRI | Start | End  | Wait Time | TAT  |\n");
    printf("+-----+--------------+------------+-----+-------+------+-----------+------+\n");
    for (int i = 0; i < size; i++)
    {
        printf("| %3d | %-12.1f | %-10.1f | %3d | %-5.1f | %-4.1f | %-9.1f | %-4.1f |\n",
               arr[i].pid, arr[i].at, arr[i].bt, arr[i].pri, arr[i].st, arr[i].et, arr[i].wt, arr[i].tat);
    }
    printf("+-----+--------------+------------+-----+-------+------+-----------+------+\n");
    printf("|                                       | Total        | %-9.1f | %-4.1f |\n", tot_wt, tot_tat);
    printf("|                                       | Average      | %-9.1f | %-4.1f |\n", tot_wt / size, tot_tat / size);
    printf("+-----+--------------+------------+-----+-------+------+-----------+------+\n\n");
}
void display_p(Process* const arr , int size)
{
    float tot_tat = 0;
    float tot_wt = 0;
    Process temp;
    for(int i = 0; i < size - 1 ; i++)
    {
        for(int j = i + 1 ; j < size ; j++)
        {
            if(arr[j].pid < arr[i].pid)
            {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        
        }
    }
    
    printf("+-----+--------------+------------+-----+-------+------+-----------+------+\n");
    printf("| PID | Arrival Time | Burst Time | PRI | Start | End  | Wait Time | TAT  |\n");
    printf("+-----+--------------+------------+-----+-------+------+-----------+------+\n");
    for (int i = 0; i < size; i++)
    {
        printf("| %3d | %-12.1f | %-10.1f | %3d | %-5.1f | %-4.1f | %-9.1f | %-4.1f |\n",
               arr[i].pid, arr[i].at, arr[i].bt, arr[i].pri, arr[i].st, arr[i].et, arr[i].wt, arr[i].tat);

        tot_tat += arr[i].tat;

        tot_wt += arr[i].wt;
    }
    printf("+-----+--------------+------------+-----+-------+------+-----------+------+\n");
    printf("|                                       | Total        | %-9.1f | %-4.1f |\n", tot_wt , tot_tat);
    printf("|                                       | Average      | %-9.1f | %-4.1f |\n", tot_wt / size , tot_tat / size);
    printf("+-----+--------------+------------+-----+-------+------+-----------+------+\n\n");

}
void priority_p(Process *const arr, const int size)
{
    int     time = 0;
    float   avgturn = 0;
    float   avgwait = 0;
    int     min;
    int     index;
    int     prev = -1;
    int     remain = 0;
    int     endtime;
    int     count = 0;
    Process gantt[20];
    
    for(int i = 0 ; i < size ; i++)
    {
        time += arr[i].bt;
    }
    
    for(int t = 0 ; remain != size; t++)
    {
        min = 9999;
        for(int i = 0; i < size; i++)
        {
            if(arr[i].at <=t && arr[i].pri < min && arr[i].rem_t > 0)
            {
                min = arr[i].pri;
                index = i;
            }
        }
        if(count != 0 && gantt[count-1].pid != arr[index].pid)
        {
            arr[index].st = t;
            gantt[count++] = arr[index];
        }
        else if(count == 0 && t == 0)
        {
            arr[index].st = t;
            gantt[count++] = arr[index];
        }
        arr[index].rem_t -= 1;
        
        if(arr[index].rem_t == 0)
        {
            remain++;
            endtime = t + 1;
            arr[index].et = t + 1;
            arr[index].tat = endtime - arr[index].at;
            arr[index].wt = endtime  - arr[index].bt - arr[index].at;
        }   
    }

    gantt_chart(gantt, count , time);
    
    display_p(arr ,  size);
}
int main(void)
{
    int size;
    int choice = 5;
    do
    {
        printf("\n\n Priority Scheduling \n\n");
        printf(" 1) Non Preemptive Priority \n");
        printf(" 2) Preemptive Priority \n");
        printf(" 3) Exit \n");
        printf(" Enter your choice : ");
        scanf("%d", &choice);
    
        switch (choice)
        {
                
            case 1 :
                    {
                        printf("\n\n Non Preemptive Priority\n\n");
                        printf(" Enter the number of processes : ");
                        scanf("%d", &size);
                        printf("\n");
                        Process *p = getProcesses(size);
                        priority_np(p, size);
                        break;
                    }
            case 2 :
                    {
    
                        printf("\n\n Preemptive Priority  \n\n");
                        printf(" Enter the number of processes : ");
                        scanf("%d", &size);
                        printf("\n");
                        Process *p = getProcesses(size);
                        priority_p(p, size);
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
