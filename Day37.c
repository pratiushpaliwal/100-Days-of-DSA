#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int heap[MAX];
int size = 0;

/* ---------- min-heap helpers ---------- */

void swap(int *a, int *b) {
    int tmp = *a; *a = *b; *b = tmp;
}

void heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            swap(&heap[parent], &heap[i]);
            i = parent;
        } else break;
    }
}

void heapifyDown(int i) {
    while (1) {
        int smallest = i;
        int left  = 2 * i + 1;
        int right = 2 * i + 2;

        if (left  < size && heap[left]  < heap[smallest]) smallest = left;
        if (right < size && heap[right] < heap[smallest]) smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else break;
    }
}

/* ---------- operations ---------- */

void insert(int x) {
    heap[size++] = x;
    heapifyUp(size - 1);
}

void deleteMin() {
    if (size == 0) { printf("-1\n"); return; }
    printf("%d\n", heap[0]);
    heap[0] = heap[--size];
    heapifyDown(0);
}

void peek() {
    if (size == 0) { printf("-1\n"); return; }
    printf("%d\n", heap[0]);
}

/* ---------- main ---------- */

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        char op[10];
        scanf("%s", op);

        if (strcmp(op, "insert") == 0) {
            int x; scanf("%d", &x);
            insert(x);
        } else if (strcmp(op, "delete") == 0) {
            deleteMin();
        } else if (strcmp(op, "peek") == 0) {
            peek();
        }
    }
    return 0;
}