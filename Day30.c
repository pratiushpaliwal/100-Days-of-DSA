// Problem: Polynomial Using Linked List - Implement using linked list with dynamic memory allocation.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coe;
    int exp;
    struct Node* next;
} Node;

Node* createNode(int coe, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coe = coe;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

Node* insert(Node* head, int coe, int exp) {
    Node* newNode = createNode(coe, exp);
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

void print(Node* head) {
    if (head == NULL) {
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        if (temp->next == NULL) {
            printf("%d", temp->coe);
        }else {
            if (temp->exp == 1) {
                printf("%dx + ", temp->coe);
            }else {
                printf("%dx^%d + ", temp->coe, temp->exp);
            }
        }
        temp = temp->next;
    }
    printf("\n");
}

Node* head = NULL;
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int coe, exp;
        scanf("%d %d", &coe, &exp);
        head = insert(head, coe, exp);
    }
    print(head);
    return 0;
}