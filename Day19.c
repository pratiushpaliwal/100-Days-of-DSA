// Problem: Given an array of integers, find two elements whose sum is closest to zero.


#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


int main() {
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i = 0; i < n; i++) {
        scanf("%d",&arr[i]);
    }

    qsort(arr, n,sizeof(int),compare);

    int left = 0, right = n - 1;
    int best_left = left, best_right = right;
    int best_sum = arr[left] + arr[right];

    while (left < right) {
        int current_sum = arr[left] + arr[right];

        if (abs(current_sum) < abs(best_sum)) {
            best_sum = current_sum;
            best_left = left;
            best_right = right;
        }

        if (current_sum < 0) {
            left++;
        } else if (current_sum > 0) {
            right--;
        } else {
            break;
        }
    }

    printf("%d %d\n", arr[best_left], arr[best_right]);

    return 0;
}