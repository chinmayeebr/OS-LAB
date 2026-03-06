#include <stdio.h>

int main()
{
    int n, i, j, temp;
    int at[20], bt[20], ct[20], tat[20], wt[20], rt[20], p[20];
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        p[i] = i+1;

        printf("\nProcess P%d\n", i+1);

        printf("Enter Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Enter Burst Time: ");
        scanf("%d",&bt[i]);
    }

    /* Sort by Arrival Time */
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(at[i] > at[j])
            {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    /* Completion Time */
    ct[0] = at[0] + bt[0];

    for(i=1;i<n;i++)
    {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    /* Calculate TAT, WT, RT */
    for(i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat = avg_tat / n;
    avg_wt = avg_wt / n;

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f", avg_wt);

    return 0;
}
