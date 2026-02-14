// Problem: Write a program to check whether a given square matrix is an Identity Matrix. An identity matrix is a square matrix in which all diagonal elements are 1 and all non-diagonal elements are 0.


#include <stdio.h>

int main() {
    int n;
    scanf("%d",&n);
    int matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d",&matrix[i][j]);
        }
    }
    int is_identity = 1;

    for (int i = 0; i < n && is_identity; i++) {
        for (int j = 0; j < n && is_identity; j++) {
            if ((i == j && matrix[i][j] != 1) || (i != j && matrix[i][j] != 0)) {
                is_identity = 0;
            }
        }
    }

    printf("%s\n", is_identity ? "Identity Matrix" : "Not an Identity Matrix");

    return 0;
}