// Problem Statement:
// Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Search Tree.


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

Node *insert(Node *root, int data) {
    if (!root) return newNode(data);
    if (data < root->data) root->left  = insert(root->left,  data);
    else if (data > root->data) root->right = insert(root->right, data);
    return root;
}

Node *lca(Node *root, int p, int q) {
    if (!root) return NULL;

    if (p < root->data && q < root->data)
        return lca(root->left,  p, q);   /* both in left subtree  */

    if (p > root->data && q > root->data)
        return lca(root->right, p, q);   /* both in right subtree */

    return root;                          /* split point = LCA     */
}

int main(void) {
    int n;
    scanf("%d", &n);

    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        root = insert(root, x);
    }

    int p, q;
    scanf("%d %d", &p, &q);

    Node *result = lca(root, p, q);
    if (result) printf("%d\n", result->data);

    return 0;
}