// Problem Statement:
// Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Tree.


#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

Node *buildTree(int *arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    Node **queue = (Node **)malloc(n * sizeof(Node *));
    int front = 0, rear = 0;
    Node *root = newNode(arr[0]);
    queue[rear++] = root;
    int i = 1;
    while (front < rear && i < n) {
        Node *curr = queue[front++];
        if (i < n && arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;
        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }
    free(queue);
    return root;
}

Node *lca(Node *root, int p, int q) {
    if (!root) return NULL;
    if (root->data == p || root->data == q) return root;
    Node *left  = lca(root->left,  p, q);
    Node *right = lca(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
}

int main(void) {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    int p, q;
    scanf("%d %d", &p, &q);
    Node *root = buildTree(arr, n);
    Node *result = lca(root, p, q);
    if (result) printf("%d\n", result->data);
    free(arr);
    return 0;
}