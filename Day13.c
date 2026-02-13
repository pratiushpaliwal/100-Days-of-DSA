// Problem: You are given a rectangular matrix of integers. Starting from the outer boundary, traverse the matrix in a clockwise manner and continue moving inward layer by layer until all elements are visited.

#include <stdio.h>
#include <stdlib.h>

void spiral_traversal(int** matrix, int r, int c) {
    int top = 0;
    int bottom = r - 1;
    int left = 0;
    int right = c - 1;
    int first = 1;

    while (top <= bottom && left <= right) {
        for (int col = left; col <= right; col++) {
            if (!first) printf(" ");
            printf("%d", matrix[top][col]);
            first = 0;
        }
        top++;

        for (int row = top; row <= bottom; row++) {
            if (!first) printf(" ");
            printf("%d", matrix[row][right]);
            first = 0;
        }
        right--;

        if (top <= bottom) {
            for (int col = right; col >= left; col--) {
                if (!first) printf(" ");
                printf("%d", matrix[bottom][col]);
                first = 0;
            }
            bottom--;
        }

        if (left <= right) {
            for (int row = bottom; row >= top; row--) {
                if (!first) printf(" ");
                printf("%d", matrix[row][left]);
                first = 0;
            }
            left++;
        }
    }
    printf("\n");
}

int main() {
    int r, c;

    scanf("%d %d", &r, &c);

    int** matrix = (int**)malloc(r * sizeof(int*));
    for (int i = 0; i < r; i++) {
        matrix[i] = (int*)malloc(c * sizeof(int));
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    spiral_traversal(matrix, r, c);

    for (int i = 0; i < r; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}