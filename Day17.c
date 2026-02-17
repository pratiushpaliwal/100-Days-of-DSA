// Problem: Write a program to find the maximum and minimum values present in a given array of integers.


#include <limits.h>
#include <stdio.h>

int main() {
    int n;
    scanf("%d",&n);
    int arr[n];
    int max = INT_MIN;
    int min = INT_MAX;
    for(int i=0;i<n;i++) {
        scanf("%d",&arr[i]);
        if(arr[i]>max) {
            max = arr[i];
        }
        if(arr[i]<min) {
            min = arr[i];
        }
    }
    printf("Max: %d\nMin: %d\n",max, min);
    return 0;
}