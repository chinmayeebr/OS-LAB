#include <stdio.h>

int main() {
    int n, r, i, j, k;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0}, safe[10];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &r);
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < r; i++)
        scanf("%d", &avail[i]);
    for(i = 0; i < n; i++)
        for(j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    k = 0;
    for(i = 0; i < n; i++) {
        for(int p = 0; p < n; p++) {
            if(!finish[p]) {
                int flag = 1;
                for(j = 0; j < r; j++) {
                    if(need[p][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if(flag) {
                    safe[k++] = p;
                    for(j = 0; j < r; j++)
                        avail[j] += alloc[p][j];
                    finish[p] = 1;
                }
            }
        }
    }
    printf("\nSafe Sequence:\n");
    for(i = 0; i < n; i++)
        printf("P%d ", safe[i]);
    return 0;
}
