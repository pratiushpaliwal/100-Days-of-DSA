// Problem: Given an array of integers, rotate the array to the right by k positions.


#include <stdio.h>

void reverse(int* arr, int i, int j) {
    while(i<j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

int main() {
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++) {
        scanf("%d",&arr[i]);
    }
    int k;
    scanf("%d",&k);
    k %= n;

    reverse(arr,0,n-1);
    reverse(arr,0,k-1);
    reverse(arr,k,n-1);

    for(int i=0;i<n;i++) {
        printf("%d ",arr[i]);
    }
    return 0;
}