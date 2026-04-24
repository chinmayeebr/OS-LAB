#include <stdio.h>
#include <stdbool.h>

#define MAX 20

typedef struct {
    int pid, at, bt, pr;
    int ct, tat, wt, resp;
    int temp_bt;
    bool completed, started;
} Process;

void print_gantt(int gantt[], int gantt_time[], int g_index) {
    for (int i = 0; i < g_index-1; i++) printf("|  P%d  ", gantt[i]);
    printf("|\n");
    printf("%d", gantt_time[0]);
    for (int i = 1; i < g_index; i++) printf("%7d", gantt_time[i]);
    printf("\n");
}

void non_preemptive_priority(Process p[], int n) {
    int time = 0, count = 0;
    int total_wt = 0, total_tat = 0;
    int gantt[MAX], gantt_time[MAX], g_index = 0;

    while (count < n) {
        int k = -1, min_pr = 9999;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].pr < min_pr) {
                min_pr = p[i].pr; k = i;
            }
        }
        if (k == -1) { time++; continue; }
        if (!p[k].started) { p[k].resp = time - p[k].at; p[k].started = true; }
        gantt[g_index] = p[k].pid;
        gantt_time[g_index] = time;
        g_index++;
        time += p[k].bt;
        p[k].ct = time; p[k].tat = p[k].ct - p[k].at; p[k].wt = p[k].tat - p[k].bt;
        total_wt += p[k].wt; total_tat += p[k].tat;
        p[k].completed = true; count++;
        gantt_time[g_index] = time;
    }

    printf("\n--- Non-Preemptive Priority Scheduling ---\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt, p[i].resp);

    printf("\nAverage Waiting Time = %.2f", (float)total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);

    printf("\nGantt Chart:\n");
    print_gantt(gantt, gantt_time, g_index+1);
}

void preemptive_priority(Process p[], int n) {
    int time = 0, completed = 0;
    int total_wt = 0, total_tat = 0;
    int gantt[MAX*MAX], gantt_time[MAX*MAX], g_index = 0;
    int current = -1;

    for (int i = 0; i < n; i++) {
        p[i].temp_bt = p[i].bt;
        p[i].completed = false;
        p[i].started = false;
    }

    gantt_time[g_index] = 0;

    while (completed < n) {
        int k = -1, min_pr = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed && p[i].pr < min_pr) {
                min_pr = p[i].pr; k = i;
            }
        }
        if (k == -1) { time++; continue; }

        if (!p[k].started) {
            p[k].resp = time - p[k].at;
            p[k].started = true;
        }

        if (current != k) {
            gantt[g_index] = p[k].pid;
            gantt_time[g_index] = time;
            g_index++;
            current = k;
        }

        p[k].temp_bt--;
        time++;

        if (p[k].temp_bt == 0) {
            p[k].ct = time;
            p[k].tat = p[k].ct - p[k].at;
            p[k].wt = p[k].tat - p[k].bt;
            total_wt += p[k].wt;
            total_tat += p[k].tat;
            p[k].completed = true;
            completed++;
        }
    }

    gantt_time[g_index] = time;

    printf("\n--- Preemptive Priority Scheduling ---\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt, p[i].resp);

    printf("\nAverage Waiting Time = %.2f", (float)total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);

    printf("\nGantt Chart:\n");
    print_gantt(gantt, gantt_time, g_index+1);
}

int main() {
    int n; Process p[MAX];
    printf("Enter number of processes: "); scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter AT, BT, PR for P%d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].completed = false; p[i].started = false;
    }
    Process p1[MAX], p2[MAX];
    for (int i = 0; i < n; i++) { p1[i] = p[i]; p2[i] = p[i]; }
    non_preemptive_priority(p1, n);
    preemptive_priority(p2, n);
    return 0;
}
