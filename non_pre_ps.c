#include <stdio.h>

int main()
{
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], pr[n];
    int ct[n], tat[n], wt[n], rt[n];
    int completed[n];

    for(i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority (Lower number = Higher priority): ");
        scanf("%d", &pr[i]);

        completed[i] = 0;
    }

    int currentTime = 0;
    int completedCount = 0;
    float avgWT = 0, avgTAT = 0, avgRT = 0;

    int gantt[n];
    int gtime[n + 1];
    int k = 0;

    while(completedCount < n)
    {
        int highest = -1;
        int bestPriority = 9999;

        for(i = 0; i < n; i++)
        {
            if(!completed[i] && at[i] <= currentTime)
            {
                if(pr[i] < bestPriority)
                {
                    bestPriority = pr[i];
                    highest = i;
                }
            }
        }

        if(highest == -1)
        {
            currentTime++;
            continue;
        }

        gtime[k] = currentTime;
        gantt[k] = highest;
        k++;

        currentTime += bt[highest];

        ct[highest] = currentTime;
        tat[highest] = ct[highest] - at[highest];
        wt[highest] = tat[highest] - bt[highest];
        rt[highest] = wt[highest];

        completed[highest] = 1;
        completedCount++;

        avgWT += wt[highest];
        avgTAT += tat[highest];
        avgRT += rt[highest];
    }

    gtime[k] = currentTime;

    avgWT /= n;
    avgTAT /= n;
    avgRT /= n;

    printf("\n\nPriority Scheduling Result\n");

    printf("--------------------------------------------------------------------------\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    printf("--------------------------------------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("--------------------------------------------------------------------------\n");

    printf("\nAverage Waiting Time    = %.2f", avgWT);
    printf("\nAverage Turnaround Time = %.2f", avgTAT);
    printf("\nAverage Response Time   = %.2f\n", avgRT);

    printf("\nGantt Chart\n\n");

    for(i = 0; i < k; i++)
        printf("+-------");
    printf("+\n");

    for(i = 0; i < k; i++)
        printf("|  P%d   ", pid[gantt[i]]);
    printf("|\n");

    for(i = 0; i < k; i++)
        printf("+-------");
    printf("+\n");

    for(i = 0; i <= k; i++)
        printf("%-8d", gtime[i]);

    printf("\n");

    return 0;
}
