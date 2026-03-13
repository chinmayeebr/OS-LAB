#include <stdio.h>
#include <limits.h>

struct process
{
    int pid, at, bt, ct, tat, wt, rt;
    int remaining, start, completed;
};

int main()
{
    int n,i,choice;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct process p[n];

    printf("\nEnter Arrival Time and Burst Time\n");
    for(i=0;i<n;i++)
    {
        p[i].pid=i+1;
        printf("P%d (AT BT): ",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);

        p[i].remaining=p[i].bt;
        p[i].completed=0;
        p[i].start=-1;
    }

    printf("\n1. SJF Non Preemptive");
    printf("\n2. SJF Preemptive (SRTF)");
    printf("\nEnter choice: ");
    scanf("%d",&choice);

    int time=0,done=0,min,idx;

    int gantt_p[100], gantt_t[100];
    int g=0;

    gantt_t[g]=0;

    if(choice==1)
    {
        while(done<n)
        {
            min=INT_MAX;
            idx=-1;

            for(i=0;i<n;i++)
            {
                if(p[i].at<=time && p[i].completed==0 && p[i].bt<min)
                {
                    min=p[i].bt;
                    idx=i;
                }
            }

            if(idx!=-1)
            {
                if(p[idx].start==-1)
                    p[idx].start=time;

                gantt_p[g]=p[idx].pid;

                time+=p[idx].bt;

                g++;
                gantt_t[g]=time;

                p[idx].ct=time;
                p[idx].completed=1;
                done++;
            }
            else
                time++;
        }
    }

    else if(choice==2)
    {
        int prev=-1;

        while(done<n)
        {
            min=INT_MAX;
            idx=-1;

            for(i=0;i<n;i++)
            {
                if(p[i].at<=time && p[i].remaining>0 && p[i].remaining<min)
                {
                    min=p[i].remaining;
                    idx=i;
                }
            }

            if(idx!=-1)
            {
                if(p[idx].start==-1)
                    p[idx].start=time;

                if(prev!=idx)
                {
                    gantt_p[g]=p[idx].pid;
                    gantt_t[g]=time;
                    g++;
                }

                p[idx].remaining--;
                time++;

                prev=idx;

                if(p[idx].remaining==0)
                {
                    p[idx].ct=time;
                    p[idx].completed=1;
                    done++;
                }
            }
            else
                time++;
        }
        gantt_t[g]=time;
    }

    else
    {
        printf("Invalid choice");
        return 0;
    }

    float avg_tat=0,avg_wt=0,avg_rt=0;

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++)
    {
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        p[i].rt=p[i].start-p[i].at;

        avg_tat+=p[i].tat;
        avg_wt+=p[i].wt;
        avg_rt+=p[i].rt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }

    printf("\nAverage TAT = %.2f",avg_tat/n);
    printf("\nAverage WT = %.2f",avg_wt/n);
    printf("\nAverage RT = %.2f\n",avg_rt/n);

    printf("\nGantt Chart:\n|");
    for(i=0;i<g;i++)
        printf(" P%d |",gantt_p[i]);

    printf("\n%d",gantt_t[0]);
    for(i=1;i<=g;i++)
        printf("    %d",gantt_t[i]);

    printf("\n");

    return 0;
}
