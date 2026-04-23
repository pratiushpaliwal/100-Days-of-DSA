/*
 * Day 82 - Upper Bound & Lower Bound Implementation
 *
 * Problem: Given a sorted array of integers and a target value x, implement
 *          the Lower Bound and Upper Bound operations using Binary Search.
 *          Lower Bound: The index of the first element >= x.
 *          Upper Bound: The index of the first element strictly > x.
 *
 * Input:
 * - First line: integer n representing the size of the array
 * - Second line: n space-separated sorted integers
 * - Third line: integer x (the target value)
 *
 * Output:
 * - Print two integers:
 *   1) Index of the lower bound of x
 *   2) Index of the upper bound of x
 *
 * Example:
 * Input:
 * 7
 * 1 2 4 4 4 5 7
 * 4
 *
 * Output:
 * 2 5
 *
 * Explanation:
 * For the given array [1, 2, 4, 4, 4, 5, 7] and x = 4:
 * - The lower bound is at index 2, which is the first occurrence of 4.
 * - The upper bound is at index 5, which is the first element greater than 4 (i.e., 5).
 * Binary Search is used to find both bounds efficiently in O(log n) time.
 */

#include <stdio.h>

/* Returns first index where arr[index] >= x */
int lowerBound(int arr[], int n, int x) {
    int low = 0, high = n - 1;
    int ans = n;

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] >= x) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

/* Returns first index where arr[index] > x */
int upperBound(int arr[], int n, int x) {
    int low = 0, high = n - 1;
    int ans = n;

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] > x) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int x;
    scanf("%d", &x);

    printf("%d %d\n", lowerBound(arr, n, x), upperBound(arr, n, x));

    return 0;
}
