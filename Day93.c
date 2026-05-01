// Day 93: Advanced Algorithms - Persistent Data Structures
// Problem: Persistent Segment Tree for Range Queries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXLOG 20

struct Node {
    int sum;
    struct Node *left, *right;
} *roots[MAXN];

int arr[MAXN];
int n, version_count = 0;

// Create a new node
struct Node* create_node(int sum, struct Node *left, struct Node *right) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->sum = sum;
    node->left = left;
    node->right = right;
    return node;
}

// Build initial segment tree
struct Node* build(int l, int r) {
    if (l == r) {
        return create_node(arr[l], NULL, NULL);
    }
    
    int mid = (l + r) / 2;
    struct Node *left_child = build(l, mid);
    struct Node *right_child = build(mid + 1, r);
    
    return create_node(left_child->sum + right_child->sum, left_child, right_child);
}

// Update segment tree (creates new version)
struct Node* update(struct Node *node, int l, int r, int pos, int new_val) {
    if (l == r) {
        return create_node(new_val, NULL, NULL);
    }
    
    int mid = (l + r) / 2;
    struct Node *left_child = node->left;
    struct Node *right_child = node->right;
    
    if (pos <= mid) {
        left_child = update(node->left, l, mid, pos, new_val);
    } else {
        right_child = update(node->right, mid + 1, r, pos, new_val);
    }
    
    return create_node(left_child->sum + right_child->sum, left_child, right_child);
}

// Query range sum
int query(struct Node *node, int l, int r, int ql, int qr) {
    if (!node || ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return node->sum;
    
    int mid = (l + r) / 2;
    return query(node->left, l, mid, ql, qr) + 
           query(node->right, mid + 1, r, ql, qr);
}

// Get value at specific position
int get_value(struct Node *node, int l, int r, int pos) {
    if (l == r) return node->sum;
    
    int mid = (l + r) / 2;
    if (pos <= mid) {
        return get_value(node->left, l, mid, pos);
    } else {
        return get_value(node->right, mid + 1, r, pos);
    }
}

// Find kth smallest element in range [ql, qr] using persistent segment tree
int kth_smallest(struct Node *left_root, struct Node *right_root, 
                 int l, int r, int k) {
    if (l == r) return l;
    
    int mid = (l + r) / 2;
    int left_count = 0;
    
    if (right_root && right_root->left) left_count += right_root->left->sum;
    if (left_root && left_root->left) left_count -= left_root->left->sum;
    
    if (k <= left_count) {
        struct Node *new_left = left_root ? left_root->left : NULL;
        struct Node *new_right = right_root ? right_root->left : NULL;
        return kth_smallest(new_left, new_right, l, mid, k);
    } else {
        struct Node *new_left = left_root ? left_root->right : NULL;
        struct Node *new_right = right_root ? right_root->right : NULL;
        return kth_smallest(new_left, new_right, mid + 1, r, k - left_count);
    }
}

// Persistent Array implementation
struct PersistentArray {
    struct Node *root;
    int size;
} persistent_arrays[MAXN];

int array_versions = 0;

// Create new version of array with update
void create_array_version(int base_version, int pos, int val) {
    if (base_version == -1) {
        // Create initial version
        for (int i = 0; i < n; i++) {
            arr[i] = 0;  // Initialize with zeros
        }
        persistent_arrays[array_versions].root = build(0, n - 1);
    } else {
        // Create new version based on existing version
        persistent_arrays[array_versions].root = 
            update(persistent_arrays[base_version].root, 0, n - 1, pos, val);
    }
    
    persistent_arrays[array_versions].size = n;
    array_versions++;
}

void print_version(int version) {
    printf("Version %d: ", version);
    for (int i = 0; i < n; i++) {
        int val = get_value(persistent_arrays[version].root, 0, n - 1, i);
        printf("%d ", val);
    }
    printf("\n");
}

// Persistent Stack implementation
struct StackNode {
    int value;
    struct StackNode *prev;
} *stack_versions[MAXN];

int stack_version_count = 0;

void push_stack(int base_version, int value) {
    struct StackNode *new_node = (struct StackNode*)malloc(sizeof(struct StackNode));
    new_node->value = value;
    
    if (base_version == -1) {
        new_node->prev = NULL;
    } else {
        new_node->prev = stack_versions[base_version];
    }
    
    stack_versions[stack_version_count++] = new_node;
}

int pop_stack(int version) {
    if (!stack_versions[version]) return -1;
    return stack_versions[version]->value;
}

void print_stack(int version) {
    printf("Stack version %d: ", version);
    struct StackNode *curr = stack_versions[version];
    
    while (curr) {
        printf("%d ", curr->value);
        curr = curr->prev;
    }
    printf("\n");
}

int main() {
    printf("Choose persistent data structure:\n");
    printf("1. Persistent Segment Tree (Range Sum Queries)\n");
    printf("2. Persistent Array\n");
    printf("3. Persistent Stack\n");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter array size: ");
        scanf("%d", &n);
        
        printf("Enter %d array elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        // Build initial version
        roots[version_count++] = build(0, n - 1);
        
        printf("\nOperations:\n");
        printf("1 pos val - Update position pos to val (creates new version)\n");
        printf("2 version l r - Query sum in range [l, r] for given version\n");
        printf("3 version pos - Get value at position pos for given version\n");
        printf("4 - Exit\n");
        
        int op;
        while (scanf("%d", &op) && op != 4) {
            if (op == 1) {
                int pos, val;
                scanf("%d %d", &pos, &val);
                roots[version_count] = update(roots[version_count - 1], 0, n - 1, pos, val);
                version_count++;
                printf("Created version %d\n", version_count - 1);
            } else if (op == 2) {
                int version, l, r;
                scanf("%d %d %d", &version, &l, &r);
                if (version >= 0 && version < version_count) {
                    int sum = query(roots[version], 0, n - 1, l, r);
                    printf("Sum in range [%d, %d] for version %d: %d\n", l, r, version, sum);
                } else {
                    printf("Invalid version\n");
                }
            } else if (op == 3) {
                int version, pos;
                scanf("%d %d", &version, &pos);
                if (version >= 0 && version < version_count) {
                    int val = get_value(roots[version], 0, n - 1, pos);
                    printf("Value at position %d for version %d: %d\n", pos, version, val);
                } else {
                    printf("Invalid version\n");
                }
            }
        }
        
    } else if (choice == 2) {
        printf("Enter array size: ");
        scanf("%d", &n);
        
        // Create initial version (all zeros)
        create_array_version(-1, 0, 0);
        
        printf("\nOperations:\n");
        printf("1 base_version pos val - Create new version based on base_version with arr[pos] = val\n");
        printf("2 version - Print version\n");
        printf("3 - Exit\n");
        
        int op;
        while (scanf("%d", &op) && op != 3) {
            if (op == 1) {
                int base_version, pos, val;
                scanf("%d %d %d", &base_version, &pos, &val);
                if (base_version >= 0 && base_version < array_versions) {
                    create_array_version(base_version, pos, val);
                    printf("Created version %d\n", array_versions - 1);
                } else {
                    printf("Invalid base version\n");
                }
            } else if (op == 2) {
                int version;
                scanf("%d", &version);
                if (version >= 0 && version < array_versions) {
                    print_version(version);
                } else {
                    printf("Invalid version\n");
                }
            }
        }
        
    } else if (choice == 3) {
        // Create initial empty stack
        push_stack(-1, 0);  // Dummy push to create version 0
        stack_version_count--;  // Reset to 0
        stack_versions[0] = NULL;
        stack_version_count = 1;
        
        printf("\nOperations:\n");
        printf("1 base_version val - Push val to create new version based on base_version\n");
        printf("2 version - Print stack version\n");
        printf("3 version - Pop from version (just shows top element)\n");
        printf("4 - Exit\n");
        
        int op;
        while (scanf("%d", &op) && op != 4) {
            if (op == 1) {
                int base_version, val;
                scanf("%d %d", &base_version, &val);
                if (base_version >= 0 && base_version < stack_version_count) {
                    push_stack(base_version, val);
                    printf("Created stack version %d\n", stack_version_count - 1);
                } else {
                    printf("Invalid base version\n");
                }
            } else if (op == 2) {
                int version;
                scanf("%d", &version);
                if (version >= 0 && version < stack_version_count) {
                    print_stack(version);
                } else {
                    printf("Invalid version\n");
                }
            } else if (op == 3) {
                int version;
                scanf("%d", &version);
                if (version >= 0 && version < stack_version_count) {
                    int top_val = pop_stack(version);
                    if (top_val != -1) {
                        printf("Top element of version %d: %d\n", version, top_val);
                    } else {
                        printf("Version %d is empty\n", version);
                    }
                } else {
                    printf("Invalid version\n");
                }
            }
        }
    }
    
    return 0;
}