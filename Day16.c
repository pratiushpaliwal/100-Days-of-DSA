// Problem: Given an array of integers, count the frequency of each distinct element and print the result.


#include <stdio.h>
#include <stdlib.h>

int compare(const void * a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n; i++) {
        int count = 1;

        while (i < n - 1 && arr[i] == arr[i + 1]) {
            count++;
            i++;
        }

        printf("%d:%d ",arr[i] ,count);
    }
    return 0;
}