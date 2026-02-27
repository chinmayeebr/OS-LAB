#include <stdio.h>

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Array must have at least two elements.\n");
        return 0;
    }

    int arr[100];   // fixed size array
    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int smallest = arr[0];
    int secondSmallest = arr[1];

    // Make sure smallest and secondSmallest are initialized correctly
    if (secondSmallest < smallest) {
        int temp = smallest;
        smallest = secondSmallest;
        secondSmallest = temp;
    }

    for (int i = 2; i < n; i++) {
        if (arr[i] < smallest) {
            secondSmallest = smallest;
            smallest = arr[i];
        } else if (arr[i] < secondSmallest && arr[i] != smallest) {
            secondSmallest = arr[i];
        }
    }

    printf("Second smallest element: %d\n", secondSmallest);

    return 0;
}
