// Problem Statement:
// Implement a Queue using a linked list supporting enqueue and dequeue operations.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Queue* q, int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
        return;
    }
    q->rear->next = node;
    q->rear = node;
}

void dequeue(struct Queue* q) {
    if (q->front == NULL) {
        printf("-1\n");
        return;
    }
    struct Node* temp = q->front;
    printf("%d\n", temp->data);
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
}

int main() {
    int n;
    scanf("%d", &n);
    struct Queue* q = createQueue();
    for (int i = 0; i < n; i++) {
        char op[10];
        scanf("%s", op);
        if (op[0] == 'E') {
            int val;
            scanf("%d", &val);
            enqueue(q, val);
        } else {
            dequeue(q);
        }
    }
    return 0;
}