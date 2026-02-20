// Problem: Given an array of integers, count the number of subarrays whose sum is equal to zero.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    

    int count = 0;
    int prefix[n + 1];
    prefix[0] = 0;
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];

    for (int i = 0; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (prefix[i] == prefix[j])
                count++;

    printf("%d\n", count);
    return 0;
}