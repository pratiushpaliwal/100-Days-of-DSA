// Problem: Rotate Linked List Right by k Places - Implement using linked list with dynamic memory allocation.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

Node* head = NULL;
Node* insert(Node* head, int val) {
    Node* newNode = createNode(val);
    if (head == NULL) {
        head = newNode;
        return head;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

void display(Node* head) {
    if (!head) {
        printf("Empty List\n");
        return;
    }
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

Node* rotate(Node* head, int n, int k) {
    if (!head) {
        printf("Empty List\n");
        return NULL;
    }
    k = k % n;
    if (k == 0) return head;

    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = head;

    int pos = n - k;
    int count = 0;
    while (count < pos) {
        count++;
        temp = temp->next;
    }
    head = temp->next;
    temp->next = NULL;
    return head;
}

int main() {
    int n;
    scanf("%d", &n);
    int val;
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        head = insert(head, val);
    }

    int k;
    scanf("%d", &k);

    head = rotate(head, n, k);
    display(head);


    return 0;
}