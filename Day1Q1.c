#include <stdio.h>

int main() {
    int n, pos, x;

    // Read number of elements
    scanf("%d", &n);

    int arr[n + 1];   // size n+1 to allow insertion

    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Read position (1-based)
    scanf("%d", &pos);

    // Read element to insert
    scanf("%d", &x);

    // Shift elements to the right
    for (int i = n; i >= pos; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert element
    arr[pos - 1] = x;

    // Print updated array
    for (int i = 0; i <= n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
