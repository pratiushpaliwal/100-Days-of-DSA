// Problem: Given a matrix, calculate the sum of its primary diagonal elements. The primary diagonal consists of elements where row index equals column index.


#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[n][m];
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
            if (i == j) {
                sum += matrix[i][j];
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}