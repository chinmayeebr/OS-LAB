#include <stdio.h>
#include <stdbool.h>

#define MAX 20

typedef struct {
    int pid, at, bt;
    int ct, tat, wt, resp;
    int temp_bt;
    bool completed, started;
} Process;

void round_robin(Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    int total_wt = 0, total_tat = 0;
    int gantt[MAX*MAX], gantt_time[MAX*MAX];
    int g_index = 0;

    for (int i = 0; i < n; i++) {
        p[i].temp_bt = p[i].bt;
        p[i].completed = false;
        p[i].started = false;
    }

    while (completed < n) {
        bool progress = false;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].temp_bt > 0) {
                progress = true;
                if (!p[i].started) {
                    p[i].resp = time - p[i].at;
                    p[i].started = true;
                }
                gantt[g_index] = p[i].pid;
                if (p[i].temp_bt > quantum) {
                    time += quantum;
                    p[i].temp_bt -= quantum;
                } else {
                    time += p[i].temp_bt;
                    p[i].temp_bt = 0;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    total_wt += p[i].wt;
                    total_tat += p[i].tat;
                    p[i].completed = true;
                    completed++;
                }
                gantt_time[g_index] = time;
                g_index++;
            }
        }
        if (!progress) time++;
    }

    printf("\n--- Round Robin Scheduling (Quantum = %d) ---\n", quantum);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].resp);

    printf("\nAverage Waiting Time = %.2f", (float)total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);
    printf("\nGantt Chart:\n");
    for (int i = 0; i < g_index; i++) {
        printf("|  P%d  ", gantt[i]);
    }
    printf("|\n");
    printf("0");
    for (int i = 0; i < g_index; i++) {
        printf("%7d", gantt_time[i]);
    }
    printf("\n");
}

int main() {
    int n, quantum; Process p[MAX];
    printf("Enter number of processes: "); scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = false; p[i].started = false;
    }
    printf("Enter Quantum Time: "); scanf("%d", &quantum);
    round_robin(p, n, quantum);
    return 0;
}
