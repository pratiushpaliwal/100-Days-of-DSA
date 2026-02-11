// Problem: Write a program to perform addition of two matrices having the same dimensions. The sum of two matrices is obtained by adding corresponding elements of the matrices.


#include <stdio.h>

int main() {

    int n, m;
    scanf("%d%d", &n, &m);
    int matrix1[n][m];
    int matrix2[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }

    int matrix3[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix3[i][j]);
        }
        printf("\n");
    }

    return 0;
}