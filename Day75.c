/*
 * Day 75 - Largest Subarray with Zero Sum
 *
 * Problem: Given an array of integers containing both positive and negative
 *          values, find the length of the longest contiguous subarray whose
 *          sum is equal to zero.
 *
 * Input Format:
 * - An integer array arr[].
 *
 * Output Format:
 * - Print the length of the longest subarray with sum equal to zero.
 *
 * Sample Input:
 * 15 -2 2 -8 1 7 10 23
 *
 * Sample Output:
 * 5
 *
 * Explanation:
 * The subarray [-2, 2, -8, 1, 7] has a sum of 0 and is the longest such subarray.
 */

#include <stdio.h>

int main() {
    int arr[1000];
    int n = 0;

    /* Read all integers from one line until newline */
    while(scanf("%d", &arr[n]) == 1)
        n++;

    int prefix[2000], index[2000], size = 0;
    int sum = 0, maxLen = 0;

    for(int i = 0; i < n; i++) {
        sum += arr[i];

        /* Subarray from 0 to i has sum 0 */
        if(sum == 0)
            maxLen = i + 1;

        /* Check if this prefix sum was seen before */
        int found = 0;
        for(int j = 0; j < size; j++) {
            if(prefix[j] == sum) {
                int len = i - index[j];
                if(len > maxLen)
                    maxLen = len;
                found = 1;
                break;
            }
        }

        /* Store first occurrence of this prefix sum */
        if(!found) {
            prefix[size] = sum;
            index[size] = i;
            size++;
        }
    }

    printf("%d\n", maxLen);
    return 0;
}
