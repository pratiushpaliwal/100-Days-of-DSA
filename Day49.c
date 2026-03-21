// Problem: BST Insert

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data  = data;
    n->left  = NULL;
    n->right = NULL;
    return n;
}

Node *insert(Node *root, int data) {
    if (root == NULL)
        return newNode(data);       /* found the empty slot */

    if (data < root->data)
        root->left  = insert(root->left,  data);   /* go left  */
    else if (data > root->data)
        root->right = insert(root->right, data);   /* go right */
    /* if data == root->data: duplicate — ignore (no insert) */

    return root;                    /* return unchanged root */
}


void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}


int main(void) {
    Node *root = NULL;

    int values[] = {8, 3, 10, 6, 14, 7};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    printf("In-order traversal: ");
    inorder(root);
    printf("\n");

    return 0;
}
