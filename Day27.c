// Problem: Find Intersection Point of Two Linked Lists - Implement using linked list with dynamic memory allocation.


#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* insert(Node* head, int data) {
    Node* newNode = createNode(data);
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
        printf("EMPTY LIST!\n");
        return;
    }
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int length(Node* head) {
    if (!head) {
        return 0;
    }
    Node* temp = head;
    int count = 0;
    while (temp) {
        temp = temp->next;
        count++;
    }
    return count;
}

int intersection(Node* head1, Node* head2) {
    int len1 = length(head1);
    int len2 = length(head2);
    Node* temp1 = head1;
    Node* temp2 = head2;

    while (len1 > len2) {
        temp1 = temp1->next;
        len1--;
    }
    while (len2 > len1) {
        temp2 = temp2->next;
        len2--;
    }
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data == temp2->data)
            return temp1->data;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return -1;
}


Node* head1 = NULL;
Node* head2 = NULL;
int main() {
    int n;
    scanf("%d",&n);
    int val;
    for (int i = 0; i < n; i++) {
        scanf("%d",&val);
        head1 = insert(head1, val);

    }
    int m;
    scanf("%d",&m);
    for (int i = 0; i < m; i++) {
        scanf("%d",&val);
        head2 = insert(head2, val);
    }

    int data = intersection(head1, head2);
    if (data == -1) {
        printf("No Intersection\n");
    }else {
        printf("%d\n", data);
    }


    return 0;
}