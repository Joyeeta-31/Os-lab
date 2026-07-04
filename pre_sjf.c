#include <stdio.h>

int main()
{
    int n, i, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rem[n];
    int ct[n], tat[n], wt[n], rt[n];
    int firstStart[n];

    // For Gantt Chart
    int ganttProcess[1000];
    int ganttTime[1001];
    int g = 0;

    for(i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rem[i] = bt[i];
        firstStart[i] = -1;
    }

    while(completed < n)
    {
        int shortest = -1;
        int min = 99999;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rem[i] > 0)
            {
                if(rem[i] < min)
                {
                    min = rem[i];
                    shortest = i;
                }
            }
        }

        if(shortest == -1)
        {
            time++;
            continue;
        }

        if(firstStart[shortest] == -1)
            firstStart[shortest] = time;

        // Store process only when it changes
        if(g == 0 || ganttProcess[g - 1] != pid[shortest])
        {
            ganttProcess[g] = pid[shortest];
            ganttTime[g] = time;
            g++;
        }

        rem[shortest]--;
        time++;

        if(rem[shortest] == 0)
        {
            completed++;

            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            rt[shortest] = firstStart[shortest] - at[shortest];
        }
    }

    ganttTime[g] = time;

    float avgWT = 0, avgTAT = 0, avgRT = 0;

    printf("\n\nSRTF (Preemptive SJF) Scheduling Result\n");

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

    for(i = 0; i < g; i++)
        printf("+-------");
    printf("+\n");

    for(i = 0; i < g; i++)
        printf("|  P%d   ", ganttProcess[i]);
    printf("|\n");

    for(i = 0; i < g; i++)
        printf("+-------");
    printf("+\n");

    for(i = 0; i <= g; i++)
        printf("%-8d", ganttTime[i]);

    printf("\n");

    return 0;
}
