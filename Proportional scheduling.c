#include <stdio.h>

int main() {
    int n, i, total = 0;
    int ticket[10];
    float prob;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        printf("Enter tickets for P%d: ", i + 1);
        scanf("%d", &ticket[i]);
        total += ticket[i];
    }
    printf("\nProportional Scheduling Probabilities:\n\n");
    for(i = 0; i < n; i++) {
        prob = (float)ticket[i] / total;
        printf("P%d -> Probability = %.2f\n",
               i + 1, prob);
    }
    return 0;
}
