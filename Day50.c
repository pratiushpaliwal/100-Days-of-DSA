// Problem: BST Search

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
    if (root == NULL) return newNode(data);
    if (data < root->data) root->left  = insert(root->left,  data);
    else if (data > root->data) root->right = insert(root->right, data);
    return root;
}

Node *search(Node *root, int key) {
    if (root == NULL || root->data == key) return root;
    if (key < root->data) return search(root->left,  key);
    return search(root->right, key);
}

int main(void) {
    Node *root = NULL;
    int values[] = {8, 3, 10, 6, 14, 7};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    int key = 6;
    Node *result = search(root, key);

    if (result)
        printf("Found: %d\n", result->data);
    else
        printf("Not found: %d\n", key);

    key = 99;
    result = search(root, key);

    if (result)
        printf("Found: %d\n", result->data);
    else
        printf("Not found: %d\n", key);

    return 0;
}
