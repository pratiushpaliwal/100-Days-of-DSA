// Problem Statement:
// Print the nodes visible when the binary tree is viewed from the right side.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *left, *right;
};

struct Node* newNode(int val) {
    struct Node* n = malloc(sizeof(struct Node));
    n->val = val; n->left = n->right = NULL;
    return n;
}

struct Node* buildTree(int* vals, int size) {
    if (size == 0 || vals[0] == -1) return NULL;
    struct Node** q = malloc(size * sizeof(struct Node*));
    struct Node* root = newNode(vals[0]);
    q[0] = root;
    int front = 0, back = 1, i = 1;
    while (front < back && i < size) {
        struct Node* node = q[front++];
        if (i < size && vals[i] != -1) { node->left = newNode(vals[i]); q[back++] = node->left; } i++;
        if (i < size && vals[i] != -1) { node->right = newNode(vals[i]); q[back++] = node->right; } i++;
    }
    free(q);
    return root;
}

void rightView(struct Node* root) {
    if (!root) return;
    struct Node** q = malloc(10000 * sizeof(struct Node*));
    int front = 0, back = 0;
    q[back++] = root;
    int first = 1;
    while (front < back) {
        int size = back - front;
        for (int j = 0; j < size; j++) {
            struct Node* node = q[front++];
            if (j == size - 1) { if (!first) printf(" "); printf("%d", node->val); first = 0; }
            if (node->left) q[back++] = node->left;
            if (node->right) q[back++] = node->right;
        }
    }
    printf("\n");
    free(q);
}

int main() {
    int n; scanf("%d", &n);
    int* vals = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &vals[i]);
    struct Node* root = buildTree(vals, n);
    rightView(root);
    free(vals);
    return 0;
}