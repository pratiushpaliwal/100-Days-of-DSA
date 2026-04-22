/*
 * Day 81 - Implement Bubble Sort
 *
 * Problem: Implement Bubble Sort - Implement the algorithm.
 *
 * Input:
 * - First line: integer n
 * - Second line: n space-separated integers
 *
 * Output:
 * - Print the sorted array or search result
 *
 * Example:
 * Input:
 * 5
 * 64 34 25 12 22
 *
 * Output:
 * 12 22 25 34 64
 */

#include <stdio.h>

void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int swapped = 0;

        for(int j = 0; j < n - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        /* Early termination: no swaps means array is sorted */
        if(!swapped)
            break;
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    bubbleSort(arr, n);

    for(int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if(i < n - 1) printf(" ");
    }
    printf("\n");

    return 0;
}
