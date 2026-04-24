#include <stdio.h>
#include <string.h>
#define M 20
typedef struct { int pid,arr,bst,cmp,tat,wt; char type[10]; } P;

void sort(P q[], int n) {
    for(int i=0;i<n-1;i++) for(int j=i+1;j<n;j++)
        if(q[i].arr>q[j].arr){P t=q[i];q[i]=q[j];q[j]=t;}
}
int fcfs(P q[], int n, int t) {
    for(int i=0;i<n;i++){
        if(t<q[i].arr)t=q[i].arr;
        t+=q[i].bst; q[i].cmp=t;
        q[i].tat=t-q[i].arr; q[i].wt=q[i].tat-q[i].bst;
    }
    return t;
}
void report(P q[], int n, char *label) {
    printf("\n%s\nPID  Type    Arr Bst Cmp TAT  WT\n",label);
    double st=0,sw=0;
    for(int i=0;i<n;i++){
        printf("%-4d %-7s %-3d %-3d %-3d %-4d %d\n",
            q[i].pid,q[i].type,q[i].arr,q[i].bst,q[i].cmp,q[i].tat,q[i].wt);
        st+=q[i].tat; sw+=q[i].wt;
    }
    if(n) printf("Avg TAT=%.2f  Avg WT=%.2f\n",st/n,sw/n);
}
int main() {
    int n; P proc[M],sQ[M],uQ[M]; int sN=0,uN=0;
    printf("Processes: "); scanf("%d",&n);
    printf("Enter PID Type(System/User) Arrival Burst:\n");
    for(int i=0;i<n;i++){
        scanf("%d %s %d %d",&proc[i].pid,proc[i].type,&proc[i].arr,&proc[i].bst);
        if(!strcmp(proc[i].type,"System")) sQ[sN++]=proc[i];
        else uQ[uN++]=proc[i];
    }
    sort(sQ,sN); sort(uQ,uN);
    int t=fcfs(sQ,sN,0); fcfs(uQ,uN,t);
    report(sQ,sN,"-- Queue 1: System (High Priority) --");
    report(uQ,uN,"-- Queue 2: User   (Low  Priority) --");
    double st=0,sw=0;
    for(int i=0;i<sN;i++){st+=sQ[i].tat;sw+=sQ[i].wt;}
    for(int i=0;i<uN;i++){st+=uQ[i].tat;sw+=uQ[i].wt;}
    printf("\nOverall Avg TAT=%.2f  Avg WT=%.2f\n",st/n,sw/n);
    P all[M]; int tot=0;
    for(int i=0;i<sN;i++) all[tot++]=sQ[i];
    for(int i=0;i<uN;i++) all[tot++]=uQ[i];
    for(int i=0;i<tot-1;i++) for(int j=i+1;j<tot;j++)
        if(all[i].cmp>all[j].cmp){P tmp=all[i];all[i]=all[j];all[j]=tmp;}
    printf("\nGantt: \n|");
    for(int i=0;i<tot;i++) printf("P%d|",all[i].pid);
    printf("\n0"); for(int i=0;i<tot;i++) printf("  %d",all[i].cmp);
    printf("\n");
}
