// Problem Statement:
// Given a binary tree, print its vertical order traversal. Nodes that lie on the same vertical line should be printed together from top to bottom and from left to right.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct QItem {
    Node *node;
    int hd;
} QItem;

typedef struct ColNode {
    int data;
    int col;
    struct ColNode *next;
} ColNode;

Node *newNode(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

Node *buildTree(int *arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    Node **queue = (Node **)malloc(n * sizeof(Node *));
    int front = 0, rear = 0, i = 1;
    Node *root = newNode(arr[0]);
    queue[rear++] = root;
    while (front < rear && i < n) {
        Node *curr = queue[front++];
        if (i < n && arr[i] != -1) { curr->left = newNode(arr[i]); queue[rear++] = curr->left; } i++;
        if (i < n && arr[i] != -1) { curr->right = newNode(arr[i]); queue[rear++] = curr->right; } i++;
    }
    free(queue);
    return root;
}

void verticalOrder(Node *root) {
    if (!root) return;

    int cap = 1024;
    QItem *q = (QItem *)malloc(cap * sizeof(QItem));
    ColNode *cols = NULL;
    int front = 0, rear = 0;
    int minHD = 0, maxHD = 0;

    q[rear++] = (QItem){root, 0};

    while (front < rear) {
        QItem item = q[front++];
        Node *curr = item.node;
        int hd = item.hd;

        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;

        ColNode *cn = (ColNode *)malloc(sizeof(ColNode));
        cn->data = curr->data;
        cn->col  = hd;
        cn->next = NULL;

        if (!cols) {
            cols = cn;
        } else {
            ColNode *tmp = cols;
            while (tmp->next) tmp = tmp->next;
            tmp->next = cn;
        }

        if (curr->left)  q[rear++] = (QItem){curr->left,  hd - 1};
        if (curr->right) q[rear++] = (QItem){curr->right, hd + 1};
    }

    for (int col = minHD; col <= maxHD; col++) {
        int first = 1;
        ColNode *tmp = cols;
        while (tmp) {
            if (tmp->col == col) {
                if (!first) printf(" ");
                printf("%d", tmp->data);
                first = 0;
            }
            tmp = tmp->next;
        }
        printf("\n");
    }

    ColNode *tmp = cols;
    while (tmp) { ColNode *nx = tmp->next; free(nx ? nx : NULL); free(tmp); tmp = nx; }
    free(q);
}

int main(void) {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    Node *root = buildTree(arr, n);
    verticalOrder(root);
    free(arr);
    return 0;
}