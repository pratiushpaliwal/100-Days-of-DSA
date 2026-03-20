// Problem: Count Leaf Nodes


#include <stdio.h>
#include <stdlib.h>

/* ── Node definition ── */
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

/* ── Helper: allocate a new node ── */
Node *newNode(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data  = data;
    n->left  = NULL;
    n->right = NULL;
    return n;
}

/* ── Count leaf nodes (recursive) ── */
int countLeaves(Node *root) {
    if (root == NULL)
        return 0;                              /* empty subtree */

    if (root->left == NULL && root->right == NULL)
        return 1;                              /* this IS a leaf */

    return countLeaves(root->left)
         + countLeaves(root->right);           /* recurse both sides */
}

/* ── Driver ── */
int main(void) {
    /*
     *        1
     *       / \
     *      2   3
     *     / \   \
     *    4   5   6
     *
     *  Leaves: 4, 5, 6  →  expected output: 3
     */
    Node *root    = newNode(1);
    root->left    = newNode(2);
    root->right   = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Leaf node count: %d\n", countLeaves(root));  /* 3 */
    return 0;
}