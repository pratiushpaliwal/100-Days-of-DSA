// Problem Statement:
// Perform inorder, preorder, and postorder traversals of a given binary tree.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

struct Node* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    struct Node* queue[1000];
    int front = 0, rear = 0;
    struct Node* root = newNode(arr[0]);
    queue[rear++] = root;
    int i = 1;
    while (front < rear && i < n) {
        struct Node* curr = queue[front++];
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
    return root;
}

void inorder(struct Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node* root) {
    if (!root) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[1000];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    struct Node* root = buildTree(arr, n);
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    return 0;
}