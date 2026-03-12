// Implement Heap Sort using a Max Heap to sort an array in ascending order. First build a max heap, then repeatedly extract the maximum element and place it at the end of the array.


#include <stdio.h>

/* ── heapify down: maintain max-heap from node i in a heap of size n ── */
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        int tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        heapify(arr, n, largest);
    }
}

/* ── heap sort ────────────────────────────────────────────────────────── */
void heapSort(int arr[], int n) {
    /* Phase 1: build max-heap (start from last non-leaf, go up to root) */
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    /* Phase 2: extract max one by one, place it at the sorted end */
    for (int i = n - 1; i > 0; i--) {
        int tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;  /* swap root with last */
        heapify(arr, i, 0);                                /* re-heapify reduced heap */
    }
}

/* ── helpers ──────────────────────────────────────────────────────────── */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d%s", arr[i], i < n - 1 ? " " : "\n");
}

int main() {
    int arr[] = {40, 10, 30, 50, 20};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before: "); printArray(arr, n);
    heapSort(arr, n);
    printf("After:  "); printArray(arr, n);
    return 0;
}