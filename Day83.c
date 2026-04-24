/*
 * Day 83 - Implement Selection Sort
 *
 * Problem: Implement Selection Sort - Implement the algorithm.
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

void selectionSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int minIdx = i;

        /* Find minimum element in unsorted portion */
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIdx])
                minIdx = j;
        }

        /* Swap minimum element with first unsorted element */
        if(minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
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

    selectionSort(arr, n);

    for(int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if(i < n - 1) printf(" ");
    }
    printf("\n");

    return 0;
}
