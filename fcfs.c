#include <stdio.h>

int main()
{
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n];
    int ct[n], tat[n], wt[n], rt[n];

    for(i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // FCFS Scheduling
    for(i = 0; i < n; i++)
    {
        if(i == 0)
        {
            if(at[i] > 0)
                ct[i] = at[i] + bt[i];
            else
                ct[i] = bt[i];
        }
        else
        {
            if(ct[i-1] < at[i])
                ct[i] = at[i] + bt[i];
            else
                ct[i] = ct[i-1] + bt[i];
        }

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];
    }

    float avgWT = 0, avgTAT = 0, avgRT = 0;

    printf("\n\nFCFS Scheduling Result\n");

    printf("-----------------------------------------------------------------\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    printf("-----------------------------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

        avgWT += wt[i];
        avgTAT += tat[i];
        avgRT += rt[i];
    }

    avgWT /= n;
    avgTAT /= n;
    avgRT /= n;

    printf("-----------------------------------------------------------------\n");

    printf("\nAverage Waiting Time    = %.2f", avgWT);
    printf("\nAverage Turnaround Time = %.2f", avgTAT);
    printf("\nAverage Response Time   = %.2f\n", avgRT);

    // -------- Gantt Chart --------
    printf("\nGantt Chart:\n\n");

    // Top border
    for(i = 0; i < n; i++)
        printf("+-------");
    printf("+\n");

    // Process names
    for(i = 0; i < n; i++)
        printf("|  P%d   ", pid[i]);
    printf("|\n");

    // Bottom border
    for(i = 0; i < n; i++)
        printf("+-------");
    printf("+\n");

    // Time values
    if(at[0] > 0)
        printf("%-8d", at[0]);
    else
        printf("%-8d", 0);

    for(i = 0; i < n; i++)
        printf("%-8d", ct[i]);

    printf("\n");

    return 0;
}
