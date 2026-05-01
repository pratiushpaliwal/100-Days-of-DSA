// Day 100: Final Review and Practice - Complete DSA Journey
// Problem: Comprehensive Review of All Major DSA Concepts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAXN 1005

// ==================== ARRAYS ====================
void array_operations() {
    printf("=== ARRAY OPERATIONS ===\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

// ==================== LINKED LISTS ====================
struct ListNode {
    int data;
    struct ListNode* next;
};

struct ListNode* create_node(int data) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->data = data;
    node->next = NULL;
    return node;
}

void linked_list_operations() {
    printf("=== LINKED LIST OPERATIONS ===\n");
    
    struct ListNode* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    
    printf("Original list: ");
    struct ListNode* temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    
    // Reverse the linked list
    struct ListNode* prev = NULL;
    struct ListNode* current = head;
    struct ListNode* next = NULL;
    
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    
    printf("Reversed list: ");
    temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n\n");
}

// ==================== STACKS ====================
struct Stack {
    int top;
    int capacity;
    int* array;
};

struct Stack* create_stack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

void push(struct Stack* stack, int item) {
    if (stack->top == stack->capacity - 1) return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (stack->top == -1) return INT_MIN;
    return stack->array[stack->top--];
}

void stack_operations() {
    printf("=== STACK OPERATIONS ===\n");
    
    struct Stack* stack = create_stack(100);
    
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    
    printf("Popped: %d\n", pop(stack));
    printf("Popped: %d\n", pop(stack));
    printf("Popped: %d\n\n", pop(stack));
    
    free(stack->array);
    free(stack);
}

// ==================== QUEUES ====================
struct Queue {
    int front, rear, size;
    int capacity;
    int* array;
};

struct Queue* create_queue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

void enqueue(struct Queue* queue, int item) {
    if (queue->size == queue->capacity) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(struct Queue* queue) {
    if (queue->size == 0) return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

void queue_operations() {
    printf("=== QUEUE OPERATIONS ===\n");
    
    struct Queue* queue = create_queue(100);
    
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    
    printf("Dequeued: %d\n", dequeue(queue));
    printf("Dequeued: %d\n", dequeue(queue));
    printf("Dequeued: %d\n\n", dequeue(queue));
    
    free(queue->array);
    free(queue);
}

// ==================== TREES ====================
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* create_tree_node(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct TreeNode* insert_bst(struct TreeNode* root, int data) {
    if (root == NULL) return create_tree_node(data);
    
    if (data < root->data) {
        root->left = insert_bst(root->left, data);
    } else if (data > root->data) {
        root->right = insert_bst(root->right, data);
    }
    
    return root;
}

void inorder_traversal(struct TreeNode* root) {
    if (root) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

void tree_operations() {
    printf("=== BINARY SEARCH TREE OPERATIONS ===\n");
    
    struct TreeNode* root = NULL;
    root = insert_bst(root, 50);
    root = insert_bst(root, 30);
    root = insert_bst(root, 70);
    root = insert_bst(root, 20);
    root = insert_bst(root, 40);
    root = insert_bst(root, 60);
    root = insert_bst(root, 80);
    
    printf("Inorder traversal: ");
    inorder_traversal(root);
    printf("\n\n");
}

// ==================== GRAPHS ====================
struct Graph {
    int vertices;
    int** adj_matrix;
};

struct Graph* create_graph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    
    graph->adj_matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adj_matrix[i] = (int*)calloc(vertices, sizeof(int));
    }
    
    return graph;
}

void add_edge(struct Graph* graph, int src, int dest) {
    graph->adj_matrix[src][dest] = 1;
    graph->adj_matrix[dest][src] = 1; // For undirected graph
}

void dfs_util(struct Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adj_matrix[vertex][i] && !visited[i]) {
            dfs_util(graph, i, visited);
        }
    }
}

void graph_operations() {
    printf("=== GRAPH OPERATIONS ===\n");
    
    struct Graph* graph = create_graph(5);
    
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 4);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 4);
    
    int* visited = (int*)calloc(graph->vertices, sizeof(int));
    
    printf("DFS traversal starting from vertex 0: ");
    dfs_util(graph, 0, visited);
    printf("\n\n");
    
    free(visited);
    for (int i = 0; i < graph->vertices; i++) {
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);
}

// ==================== DYNAMIC PROGRAMMING ====================
int fibonacci_dp(int n) {
    if (n <= 1) return n;
    
    int* dp = (int*)malloc((n + 1) * sizeof(int));
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    int result = dp[n];
    free(dp);
    return result;
}

int knapsack_dp(int weights[], int values[], int n, int capacity) {
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)calloc(capacity + 1, sizeof(int));
    }
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w]) ?
                           values[i - 1] + dp[i - 1][w - weights[i - 1]] : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    int result = dp[n][capacity];
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

void dynamic_programming_examples() {
    printf("=== DYNAMIC PROGRAMMING EXAMPLES ===\n");
    
    printf("Fibonacci(10) = %d\n", fibonacci_dp(10));
    
    int weights[] = {10, 20, 30};
    int values[] = {60, 100, 120};
    int n = 3;
    int capacity = 50;
    
    printf("Knapsack (capacity=50): %d\n\n", knapsack_dp(weights, values, n, capacity));
}

// ==================== SEARCHING ALGORITHMS ====================
int binary_search(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    return -1;
}

void searching_algorithms() {
    printf("=== SEARCHING ALGORITHMS ===\n");
    
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 10;
    
    int result = binary_search(arr, n, target);
    if (result != -1) {
        printf("Element %d found at index %d\n\n", target, result);
    } else {
        printf("Element %d not found\n\n", target);
    }
}

// ==================== HASHING ====================
#define HASH_SIZE 10

struct HashNode {
    int key;
    int value;
    struct HashNode* next;
};

struct HashTable {
    struct HashNode* table[HASH_SIZE];
};

int hash_function(int key) {
    return key % HASH_SIZE;
}

void hash_insert(struct HashTable* ht, int key, int value) {
    int index = hash_function(key);
    
    struct HashNode* new_node = (struct HashNode*)malloc(sizeof(struct HashNode));
    new_node->key = key;
    new_node->value = value;
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
}

int hash_search(struct HashTable* ht, int key) {
    int index = hash_function(key);
    struct HashNode* current = ht->table[index];
    
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    return -1; // Not found
}

void hashing_example() {
    printf("=== HASHING EXAMPLE ===\n");
    
    struct HashTable ht = {0};
    
    hash_insert(&ht, 1, 10);
    hash_insert(&ht, 2, 20);
    hash_insert(&ht, 11, 30); // Will collide with key 1
    
    printf("Value for key 1: %d\n", hash_search(&ht, 1));
    printf("Value for key 2: %d\n", hash_search(&ht, 2));
    printf("Value for key 11: %d\n\n", hash_search(&ht, 11));
}

// ==================== MAIN FUNCTION ====================
void print_congratulations() {
    printf("🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉\n");
    printf("🎉                                                🎉\n");
    printf("🎉        CONGRATULATIONS!                       🎉\n");
    printf("🎉                                                🎉\n");
    printf("🎉    You have completed the                     🎉\n");
    printf("🎉    100 DAYS OF DSA CHALLENGE!                 🎉\n");
    printf("🎉                                                🎉\n");
    printf("🎉    Journey Summary:                           🎉\n");
    printf("🎉    ✅ Arrays & Strings                        🎉\n");
    printf("🎉    ✅ Linked Lists                            🎉\n");
    printf("🎉    ✅ Stacks & Queues                         🎉\n");
    printf("🎉    ✅ Trees & Binary Search Trees             🎉\n");
    printf("🎉    ✅ Graphs & Graph Algorithms               🎉\n");
    printf("🎉    ✅ Dynamic Programming                     🎉\n");
    printf("🎉    ✅ Sorting & Searching                     🎉\n");
    printf("🎉    ✅ Hashing & Hash Tables                   🎉\n");
    printf("🎉    ✅ Advanced Algorithms                     🎉\n");
    printf("🎉    ✅ Problem Solving Techniques              🎉\n");
    printf("🎉                                                🎉\n");
    printf("🎉    You are now ready for:                     🎉\n");
    printf("🎉    • Technical Interviews                     🎉\n");
    printf("🎉    • Competitive Programming                  🎉\n");
    printf("🎉    • Advanced Software Development            🎉\n");
    printf("🎉                                                🎉\n");
    printf("🎉    Keep practicing and never stop learning!   🎉\n");
    printf("🎉                                                🎉\n");
    printf("🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉\n\n");
}

void print_final_stats() {
    printf("📊 FINAL STATISTICS 📊\n");
    printf("========================\n");
    printf("Total Days Completed: 100\n");
    printf("Topics Covered: 95+\n");
    printf("Problems Solved: 100+\n");
    printf("Lines of Code Written: 10,000+\n");
    printf("Data Structures Mastered: 15+\n");
    printf("Algorithms Implemented: 50+\n");
    printf("Time Complexity Analyzed: ∞\n");
    printf("Space Complexity Optimized: ∞\n");
    printf("Debugging Skills: Expert Level\n");
    printf("Problem Solving: Advanced\n\n");
}

void show_next_steps() {
    printf("🚀 WHAT'S NEXT? 🚀\n");
    printf("==================\n");
    printf("1. 📚 Advanced Topics to Explore:\n");
    printf("   • System Design\n");
    printf("   • Machine Learning Algorithms\n");
    printf("   • Distributed Systems\n");
    printf("   • Database Internals\n");
    printf("   • Compiler Design\n\n");
    
    printf("2. 💼 Career Opportunities:\n");
    printf("   • Software Engineer\n");
    printf("   • Data Scientist\n");
    printf("   • Algorithm Engineer\n");
    printf("   • Research Scientist\n");
    printf("   • Technical Lead\n\n");
    
    printf("3. 🏆 Competitive Programming:\n");
    printf("   • LeetCode Contests\n");
    printf("   • Codeforces\n");
    printf("   • AtCoder\n");
    printf("   • Google Code Jam\n");
    printf("   • ACM ICPC\n\n");
    
    printf("4. 📖 Recommended Books:\n");
    printf("   • \"Introduction to Algorithms\" by CLRS\n");
    printf("   • \"Algorithm Design\" by Kleinberg & Tardos\n");
    printf("   • \"Competitive Programming\" by Halim\n");
    printf("   • \"System Design Interview\" by Alex Xu\n\n");
}

int main() {
    printf("DAY 100: FINAL REVIEW AND PRACTICE\n");
    printf("===================================\n\n");
    
    printf("Welcome to the final day of your 100 Days DSA Journey!\n");
    printf("Let's review all the major concepts you've mastered:\n\n");
    
    // Demonstrate all major DSA concepts
    array_operations();
    linked_list_operations();
    stack_operations();
    queue_operations();
    tree_operations();
    graph_operations();
    dynamic_programming_examples();
    searching_algorithms();
    hashing_example();
    
    // Celebration and final messages
    print_congratulations();
    print_final_stats();
    show_next_steps();
    
    printf("🌟 Remember: The journey of learning never ends!\n");
    printf("🌟 Keep coding, keep learning, keep growing!\n");
    printf("🌟 You've got this! 💪\n\n");
    
    printf("Thank you for completing the 100 Days of DSA Challenge!\n");
    printf("Date Completed: May 1, 2026\n");
    printf("Challenge Duration: February 1, 2026 - May 1, 2026\n\n");
    
    return 0;
}