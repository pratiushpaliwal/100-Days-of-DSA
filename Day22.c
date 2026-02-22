// Problem: Count Nodes in Linked List


#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
}Node;

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

int main() {
    int n;
    scanf("%d", &n);

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        Node* node = createNode(val);
        if (head == NULL) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
    printf("Count = %d\n", count);

    return 0;
}