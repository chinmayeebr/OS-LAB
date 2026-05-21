#include <stdio.h>

int main() {
    int n, r, i, j, k;
    int alloc[10][10], request[10][10];
    int avail[10], finish[10] = {0};
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &r);
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < r; j++)
            scanf("%d", &request[i][j]);
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < r; i++)
        scanf("%d", &avail[i]);
    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            if(!finish[i]) {
                int flag = 1;
                for(j = 0; j < r; j++) {
                    if(request[i][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if(flag) {
                    printf("P%d executed\n", i);
                    for(j = 0; j < r; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = 1;
                }
            }
        }
    }
    int deadlock = 0;
    for(i = 0; i < n; i++) {
        if(!finish[i]) {
            deadlock = 1;
            printf("P%d is in Deadlock\n", i);
        }
    }
    if(!deadlock)
        printf("\nNo Deadlock Detected");
    return 0;
}
