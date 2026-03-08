// Problem: Circular Queue Using Array - Implement using linked list with dynamic memory allocation.

#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Queue with front and rear pointers
struct Queue {
    struct Node* front;
    struct Node* rear;
    int size;
};

struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueue(struct Queue* q, int data) {
    struct Node* node = createNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
    q->size++;
}

int dequeue(struct Queue* q) {
    if (q->front == NULL) return -1;
    struct Node* temp = q->front;
    int val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    q->size--;
    return val;
}

// Circular rotate: dequeue from front, enqueue at rear
void rotateQueue(struct Queue* q, int m) {
    for (int i = 0; i < m; i++) {
        int val = dequeue(q);
        if (val != -1)
            enqueue(q, val);
    }
}

void display(struct Queue* q) {
    struct Node* temp = q->front;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" ");
        temp = temp->next;
    }
    printf("\n");
}

void freeQueue(struct Queue* q) {
    struct Node* temp = q->front;
    while (temp != NULL) {
        struct Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(q);
}

int main() {
    int n, m, val;
    scanf("%d", &n);

    struct Queue* q = createQueue();
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        enqueue(q, val);
    }

    scanf("%d", &m);
    rotateQueue(q, m);
    display(q);

    freeQueue(q);
    return 0;
}