#include <stdio.h>

int main() {
    int n;

    printf("Enter the order of square matrix: ");
    scanf("%d", &n);

    int matrix[100][100];
    int sum = 0;

    printf("Enter the elements of the matrix:\n");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for(int i = 0; i < n; i++) {
        sum += matrix[i][i];   // Left diagonal condition
    }

    printf("Sum of left diagonal = %d\n", sum);

    return 0;
}
