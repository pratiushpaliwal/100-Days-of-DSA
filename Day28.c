// Problem: Circular Linked List Creation and Traversal - Implement using linked list with dynamic memory allocation.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* create_node(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

Node* insert(Node* head, int val) {
    Node* node = create_node(val);
    if (head == NULL) {
        head = node;
        node->next = head;
        return head;
    }
    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = node;
    node->next = head;
    return head;
}

void print(Node* head) {
    if (head == NULL) {
        printf("Empty List\n");
        return;
    }
    Node* temp = head;
    while (temp->next != head) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

Node* head = NULL;

int main() {
    int n;
    scanf("%d", &n);
    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        head = insert(head, x);
    }

    print(head);

    return 0;
}