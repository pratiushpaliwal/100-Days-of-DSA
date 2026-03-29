// Problem Statement:
// Convert a binary tree into its mirror image by swapping left and right children at every node.


#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

TreeNode* buildTree(int* values, int n) {
    if (n == 0 || values[0] == -1) return NULL;
    TreeNode** queue = (TreeNode**)malloc(n * sizeof(TreeNode*));
    int front = 0, rear = 0;
    TreeNode* root = newNode(values[0]);
    queue[rear++] = root;
    int i = 1;
    while (front < rear && i < n) {
        TreeNode* node = queue[front++];
        if (i < n && values[i] != -1) {
            node->left = newNode(values[i]);
            queue[rear++] = node->left;
        }
        i++;
        if (i < n && values[i] != -1) {
            node->right = newNode(values[i]);
            queue[rear++] = node->right;
        }
        i++;
    }
    free(queue);
    return root;
}

void mirror(TreeNode* root) {
    if (!root) return;
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}

int first = 1;
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    if (!first) printf(" ");
    printf("%d", root->val);
    first = 0;
    inorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    int* values = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &values[i]);
    TreeNode* root = buildTree(values, n);
    mirror(root);
    inorder(root);
    printf("\n");
    free(values);
    return 0;
}