
#include <stdio.h>

#define MAX 100

int main()
{
    int n, tq, i;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    int pid[MAX], at[MAX], bt[MAX];
    int rem[MAX], ct[MAX], tat[MAX], wt[MAX], rt[MAX];
    int visited[MAX]={0};
    int firstResponse[MAX];

    for(i=0;i<n;i++)
    {
        pid[i]=i+1;

        printf("\nProcess P%d\n",pid[i]);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        rem[i]=bt[i];
        firstResponse[i]=-1;
    }

    // Queue
    int queue[MAX];
    int front=0,rear=0;

    // Gantt Chart
    int gantt[MAX];
    int gtime[MAX];
    int g=0;

    int currentTime=0;
    int completed=0;

        // Insert first arriving process
    int first=0;

    for(i=1;i<n;i++)
    {
        if(at[i]<at[first])
            first=i;
    }

    currentTime=at[first];

    queue[rear++]=first;
    visited[first]=1;

        while(front<rear)
    {
        int p=queue[front++];

        if(firstResponse[p]==-1)
            firstResponse[p]=currentTime;

        gantt[g]=p;
        gtime[g]=currentTime;
        g++;

        if(rem[p]>tq)
        {
            rem[p]-=tq;
            currentTime+=tq;
        }
        else
        {
            currentTime+=rem[p];
            rem[p]=0;
            completed++;

            ct[p]=currentTime;
        }

        // Add newly arrived processes
        for(i=0;i<n;i++)
        {
            if(!visited[i] && at[i]<=currentTime)
            {
                queue[rear++]=i;
                visited[i]=1;
            }
        }

        // Put current process back into queue
        if(rem[p]>0)
            queue[rear++]=p;

        // CPU Idle
        if(front==rear && completed<n)
        {
            for(i=0;i<n;i++)
            {
                if(!visited[i])
                {
                    currentTime=at[i];
                    queue[rear++]=i;
                    visited[i]=1;
                    break;
                }
            }
        }
    }

    gtime[g]=currentTime;

        float avgWT = 0, avgTAT = 0, avgRT = 0;

    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = firstResponse[i] - at[i];

        avgWT += wt[i];
        avgTAT += tat[i];
        avgRT += rt[i];
    }

    avgWT /= n;
    avgTAT /= n;
    avgRT /= n;

    printf("\n\nRound Robin Scheduling Result\n");

    printf("-------------------------------------------------------------------------------\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    printf("-------------------------------------------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("-------------------------------------------------------------------------------\n");

    printf("\nAverage Waiting Time    = %.2f", avgWT);
    printf("\nAverage Turnaround Time = %.2f", avgTAT);
    printf("\nAverage Response Time   = %.2f\n", avgRT);
        // ---------------- Ready Queue ----------------
    printf("\nReady Queue Order:\n\n");

    printf("Front -> ");

    for(i = 0; i < rear; i++)
        printf("P%d ", pid[queue[i]]);

    printf("<- Rear\n");

    // ---------------- Gantt Chart ----------------
    printf("\nGantt Chart\n\n");

    for(i = 0; i < g; i++)
        printf("+-------");
    printf("+\n");

    for(i = 0; i < g; i++)
        printf("|  P%d   ", pid[gantt[i]]);
    printf("|\n");

    for(i = 0; i < g; i++)
        printf("+-------");
    printf("+\n");

    for(i = 0; i <= g; i++)
        printf("%-8d", gtime[i]);

    printf("\n");



        return 0;
}
