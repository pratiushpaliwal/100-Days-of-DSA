// Day 94: Advanced Algorithms - Randomized Algorithms
// Problem: Randomized Quick Sort and Monte Carlo Methods

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXN 100005
#define PI 3.14159265359

int arr[MAXN];
int n;

// Random number generator
int random_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Randomized partition for quick sort
int randomized_partition(int low, int high) {
    // Choose random pivot
    int random_pivot = random_range(low, high);
    swap(&arr[random_pivot], &arr[high]);
    
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Randomized Quick Sort
void randomized_quick_sort(int low, int high) {
    if (low < high) {
        int pi = randomized_partition(low, high);
        
        randomized_quick_sort(low, pi - 1);
        randomized_quick_sort(pi + 1, high);
    }
}

// Randomized Select (find kth smallest element)
int randomized_select(int low, int high, int k) {
    if (low == high) return arr[low];
    
    int pi = randomized_partition(low, high);
    int rank = pi - low + 1;
    
    if (k == rank) {
        return arr[pi];
    } else if (k < rank) {
        return randomized_select(low, pi - 1, k);
    } else {
        return randomized_select(pi + 1, high, k - rank);
    }
}

// Monte Carlo method to estimate π
double estimate_pi(int num_points) {
    int points_inside_circle = 0;
    
    for (int i = 0; i < num_points; i++) {
        double x = (double)rand() / RAND_MAX;  // Random x in [0, 1]
        double y = (double)rand() / RAND_MAX;  // Random y in [0, 1]
        
        // Check if point is inside unit circle
        if (x * x + y * y <= 1.0) {
            points_inside_circle++;
        }
    }
    
    // π/4 = (points inside circle) / (total points)
    return 4.0 * points_inside_circle / num_points;
}

// Monte Carlo integration to estimate definite integral
// Estimate integral of f(x) = x^2 from 0 to 1
double monte_carlo_integration(int num_points) {
    double sum = 0.0;
    
    for (int i = 0; i < num_points; i++) {
        double x = (double)rand() / RAND_MAX;  // Random x in [0, 1]
        double fx = x * x;  // f(x) = x^2
        sum += fx;
    }
    
    // Average value * interval length
    return sum / num_points;
}

// Randomized algorithm for finding majority element
int find_majority_element(int iterations) {
    for (int iter = 0; iter < iterations; iter++) {
        // Pick random element
        int candidate = arr[random_range(0, n - 1)];
        
        // Count occurrences
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] == candidate) {
                count++;
            }
        }
        
        // Check if it's majority
        if (count > n / 2) {
            return candidate;
        }
    }
    
    return -1;  // No majority element found
}

// Randomized primality test (Miller-Rabin)
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    
    return result;
}

int miller_rabin_test(long long n, long long a) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;
    
    // Write n-1 as d * 2^r
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    // Compute a^d mod n
    long long x = mod_exp(a, d, n);
    
    if (x == 1 || x == n - 1) return 1;
    
    for (int i = 0; i < r - 1; i++) {
        x = (x * x) % n;
        if (x == n - 1) return 1;
    }
    
    return 0;
}

int is_prime_probabilistic(long long n, int k) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;
    
    // Test with k random witnesses
    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 3);
        if (!miller_rabin_test(n, a)) {
            return 0;  // Composite
        }
    }
    
    return 1;  // Probably prime
}

// Skip list implementation (randomized data structure)
struct SkipListNode {
    int value;
    struct SkipListNode **forward;
    int level;
};

struct SkipList {
    struct SkipListNode *header;
    int max_level;
    int current_level;
};

#define MAX_LEVEL 16

struct SkipList* create_skip_list() {
    struct SkipList *list = (struct SkipList*)malloc(sizeof(struct SkipList));
    list->max_level = MAX_LEVEL;
    list->current_level = 0;
    
    list->header = (struct SkipListNode*)malloc(sizeof(struct SkipListNode));
    list->header->forward = (struct SkipListNode**)malloc(sizeof(struct SkipListNode*) * (MAX_LEVEL + 1));
    list->header->level = MAX_LEVEL;
    
    for (int i = 0; i <= MAX_LEVEL; i++) {
        list->header->forward[i] = NULL;
    }
    
    return list;
}

int random_level() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

void skip_list_insert(struct SkipList *list, int value) {
    struct SkipListNode *update[MAX_LEVEL + 1];
    struct SkipListNode *current = list->header;
    
    // Find position to insert
    for (int i = list->current_level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (!current || current->value != value) {
        int new_level = random_level();
        
        if (new_level > list->current_level) {
            for (int i = list->current_level + 1; i <= new_level; i++) {
                update[i] = list->header;
            }
            list->current_level = new_level;
        }
        
        struct SkipListNode *new_node = (struct SkipListNode*)malloc(sizeof(struct SkipListNode));
        new_node->value = value;
        new_node->level = new_level;
        new_node->forward = (struct SkipListNode**)malloc(sizeof(struct SkipListNode*) * (new_level + 1));
        
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
    }
}

int skip_list_search(struct SkipList *list, int value) {
    struct SkipListNode *current = list->header;
    
    for (int i = list->current_level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
    }
    
    current = current->forward[0];
    return (current && current->value == value);
}

void print_array() {
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    
    printf("Choose randomized algorithm:\n");
    printf("1. Randomized Quick Sort\n");
    printf("2. Randomized Select (kth smallest)\n");
    printf("3. Monte Carlo π estimation\n");
    printf("4. Monte Carlo integration\n");
    printf("5. Randomized majority element\n");
    printf("6. Miller-Rabin primality test\n");
    printf("7. Skip List operations\n");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter array size: ");
        scanf("%d", &n);
        
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        printf("Original array:\n");
        print_array();
        
        randomized_quick_sort(0, n - 1);
        
        printf("Sorted array:\n");
        print_array();
        
    } else if (choice == 2) {
        printf("Enter array size: ");
        scanf("%d", &n);
        
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        int k;
        printf("Enter k (1-indexed): ");
        scanf("%d", &k);
        
        int kth_element = randomized_select(0, n - 1, k);
        printf("%dth smallest element: %d\n", k, kth_element);
        
    } else if (choice == 3) {
        int num_points;
        printf("Enter number of random points: ");
        scanf("%d", &num_points);
        
        double estimated_pi = estimate_pi(num_points);
        printf("Estimated π: %.6f\n", estimated_pi);
        printf("Actual π: %.6f\n", PI);
        printf("Error: %.6f\n", fabs(estimated_pi - PI));
        
    } else if (choice == 4) {
        int num_points;
        printf("Enter number of random points: ");
        scanf("%d", &num_points);
        
        double estimated_integral = monte_carlo_integration(num_points);
        printf("Estimated integral of x² from 0 to 1: %.6f\n", estimated_integral);
        printf("Actual value: %.6f\n", 1.0/3.0);
        printf("Error: %.6f\n", fabs(estimated_integral - 1.0/3.0));
        
    } else if (choice == 5) {
        printf("Enter array size: ");
        scanf("%d", &n);
        
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        int majority = find_majority_element(20);  // 20 iterations
        if (majority != -1) {
            printf("Majority element: %d\n", majority);
        } else {
            printf("No majority element found\n");
        }
        
    } else if (choice == 6) {
        long long num;
        int k;
        printf("Enter number to test: ");
        scanf("%lld", &num);
        printf("Enter number of iterations: ");
        scanf("%d", &k);
        
        if (is_prime_probabilistic(num, k)) {
            printf("%lld is probably prime\n", num);
        } else {
            printf("%lld is composite\n", num);
        }
        
    } else if (choice == 7) {
        struct SkipList *list = create_skip_list();
        
        printf("Skip List operations:\n");
        printf("1 val - Insert val\n");
        printf("2 val - Search val\n");
        printf("3 - Exit\n");
        
        int op;
        while (scanf("%d", &op) && op != 3) {
            if (op == 1) {
                int val;
                scanf("%d", &val);
                skip_list_insert(list, val);
                printf("Inserted %d\n", val);
            } else if (op == 2) {
                int val;
                scanf("%d", &val);
                if (skip_list_search(list, val)) {
                    printf("%d found in skip list\n", val);
                } else {
                    printf("%d not found in skip list\n", val);
                }
            }
        }
    }
    
    return 0;
}