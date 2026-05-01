// Day 99: Problem Solving - Optimization Techniques
// Problem: Advanced Optimization and Performance Techniques

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define MAXN 100005

// Technique 1: Memoization for Fibonacci
long long memo[MAXN];
int memo_initialized = 0;

void init_memo() {
    if (!memo_initialized) {
        for (int i = 0; i < MAXN; i++) {
            memo[i] = -1;
        }
        memo_initialized = 1;
    }
}

long long fibonacci_memo(int n) {
    init_memo();
    
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    
    memo[n] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2);
    return memo[n];
}

// Technique 2: Tabulation for Fibonacci (Bottom-up DP)
long long fibonacci_tabulation(int n) {
    if (n <= 1) return n;
    
    long long *dp = (long long*)malloc((n + 1) * sizeof(long long));
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    long long result = dp[n];
    free(dp);
    return result;
}

// Technique 3: Space-Optimized Fibonacci
long long fibonacci_optimized(int n) {
    if (n <= 1) return n;
    
    long long prev2 = 0, prev1 = 1;
    
    for (int i = 2; i <= n; i++) {
        long long current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

// Technique 4: Binary Search Optimization
int binary_search_optimized(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Technique 5: Two Pointers for Pair Sum
int* two_sum_optimized(int arr[], int n, int target, int* result_size) {
    // Assuming array is sorted
    int left = 0, right = n - 1;
    int *result = (int*)malloc(2 * sizeof(int));
    *result_size = 0;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            result[0] = left;
            result[1] = right;
            *result_size = 2;
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    free(result);
    return NULL;
}

// Technique 6: Sliding Window for Maximum Sum Subarray of Size K
int max_sum_subarray_k(int arr[], int n, int k) {
    if (n < k) return -1;
    
    // Calculate sum of first window
    int window_sum = 0;
    for (int i = 0; i < k; i++) {
        window_sum += arr[i];
    }
    
    int max_sum = window_sum;
    
    // Slide the window
    for (int i = k; i < n; i++) {
        window_sum = window_sum - arr[i - k] + arr[i];
        max_sum = (max_sum > window_sum) ? max_sum : window_sum;
    }
    
    return max_sum;
}

// Technique 7: Prefix Sum for Range Queries
struct PrefixSum {
    int *prefix;
    int size;
};

struct PrefixSum* create_prefix_sum(int arr[], int n) {
    struct PrefixSum *ps = (struct PrefixSum*)malloc(sizeof(struct PrefixSum));
    ps->prefix = (int*)malloc((n + 1) * sizeof(int));
    ps->size = n;
    
    ps->prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        ps->prefix[i] = ps->prefix[i - 1] + arr[i - 1];
    }
    
    return ps;
}

int range_sum_query(struct PrefixSum *ps, int left, int right) {
    return ps->prefix[right + 1] - ps->prefix[left];
}

// Technique 8: Bit Manipulation Optimizations
int count_set_bits(int n) {
    int count = 0;
    while (n) {
        count++;
        n &= (n - 1);  // Remove rightmost set bit
    }
    return count;
}

int is_power_of_two(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int multiply_by_power_of_two(int n, int power) {
    return n << power;  // n * 2^power
}

int divide_by_power_of_two(int n, int power) {
    return n >> power;  // n / 2^power
}

// Technique 9: Fast GCD using Binary GCD (Stein's Algorithm)
int gcd_binary(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    
    // Find the greatest power of 2 that divides both a and b
    int shift = 0;
    while (((a | b) & 1) == 0) {
        a >>= 1;
        b >>= 1;
        shift++;
    }
    
    // Remove all factors of 2 from a
    while ((a & 1) == 0) {
        a >>= 1;
    }
    
    do {
        // Remove all factors of 2 from b
        while ((b & 1) == 0) {
            b >>= 1;
        }
        
        // Ensure a <= b
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        
        b = b - a;
    } while (b != 0);
    
    return a << shift;
}

// Technique 10: Cache-Friendly Matrix Multiplication
void matrix_multiply_optimized(int **A, int **B, int **C, int n) {
    // Block size for cache optimization
    int block_size = 64;
    
    for (int ii = 0; ii < n; ii += block_size) {
        for (int jj = 0; jj < n; jj += block_size) {
            for (int kk = 0; kk < n; kk += block_size) {
                
                // Multiply blocks
                for (int i = ii; i < ii + block_size && i < n; i++) {
                    for (int j = jj; j < jj + block_size && j < n; j++) {
                        for (int k = kk; k < kk + block_size && k < n; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

// Technique 11: Loop Unrolling for Sum Calculation
long long sum_array_unrolled(int arr[], int n) {
    long long sum = 0;
    int i = 0;
    
    // Process 4 elements at a time
    for (; i <= n - 4; i += 4) {
        sum += arr[i] + arr[i + 1] + arr[i + 2] + arr[i + 3];
    }
    
    // Handle remaining elements
    for (; i < n; i++) {
        sum += arr[i];
    }
    
    return sum;
}

// Technique 12: Memory Pool for Frequent Allocations
struct MemoryPool {
    void *pool;
    size_t block_size;
    size_t num_blocks;
    void **free_list;
    int free_count;
};

struct MemoryPool* create_memory_pool(size_t block_size, size_t num_blocks) {
    struct MemoryPool *pool = (struct MemoryPool*)malloc(sizeof(struct MemoryPool));
    
    pool->block_size = block_size;
    pool->num_blocks = num_blocks;
    pool->pool = malloc(block_size * num_blocks);
    pool->free_list = (void**)malloc(num_blocks * sizeof(void*));
    pool->free_count = num_blocks;
    
    // Initialize free list
    char *ptr = (char*)pool->pool;
    for (size_t i = 0; i < num_blocks; i++) {
        pool->free_list[i] = ptr + i * block_size;
    }
    
    return pool;
}

void* pool_alloc(struct MemoryPool *pool) {
    if (pool->free_count == 0) return NULL;
    
    return pool->free_list[--pool->free_count];
}

void pool_free(struct MemoryPool *pool, void *ptr) {
    if (pool->free_count < pool->num_blocks) {
        pool->free_list[pool->free_count++] = ptr;
    }
}

// Performance measurement utility
double measure_time(void (*func)(), int iterations) {
    clock_t start = clock();
    
    for (int i = 0; i < iterations; i++) {
        func();
    }
    
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Test functions for performance comparison
void test_fibonacci_naive() {
    // Naive recursive fibonacci (very slow for large n)
    // fibonacci_naive(30);  // Commented out as it's too slow
}

void test_fibonacci_memo() {
    fibonacci_memo(40);
}

void test_fibonacci_optimized() {
    fibonacci_optimized(40);
}

void benchmark_fibonacci() {
    printf("Fibonacci Performance Comparison (n=40):\n");
    
    double time_memo = measure_time(test_fibonacci_memo, 1000);
    printf("Memoization: %.6f seconds\n", time_memo);
    
    double time_optimized = measure_time(test_fibonacci_optimized, 1000);
    printf("Space-optimized: %.6f seconds\n", time_optimized);
    
    printf("Speedup: %.2fx\n", time_memo / time_optimized);
}

int main() {
    printf("Choose an optimization technique to demonstrate:\n");
    printf("1. Fibonacci Optimization Comparison\n");
    printf("2. Binary Search vs Linear Search\n");
    printf("3. Two Pointers vs Nested Loops\n");
    printf("4. Sliding Window vs Naive Approach\n");
    printf("5. Prefix Sum for Range Queries\n");
    printf("6. Bit Manipulation Tricks\n");
    printf("7. Fast GCD Algorithm\n");
    printf("8. Loop Unrolling Demo\n");
    printf("9. Memory Pool Demo\n");
    printf("10. Performance Benchmark\n");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        int n;
        printf("Enter n for Fibonacci: ");
        scanf("%d", &n);
        
        printf("Fibonacci(%d) using different methods:\n", n);
        printf("Memoization: %lld\n", fibonacci_memo(n));
        printf("Tabulation: %lld\n", fibonacci_tabulation(n));
        printf("Space-optimized: %lld\n", fibonacci_optimized(n));
        
    } else if (choice == 2) {
        int n, target;
        printf("Enter array size and target: ");
        scanf("%d %d", &n, &target);
        
        int *arr = (int*)malloc(n * sizeof(int));
        printf("Enter %d sorted elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        int index = binary_search_optimized(arr, n, target);
        if (index != -1) {
            printf("Element found at index: %d\n", index);
        } else {
            printf("Element not found\n");
        }
        
        free(arr);
        
    } else if (choice == 3) {
        int n, target;
        printf("Enter array size and target sum: ");
        scanf("%d %d", &n, &target);
        
        int *arr = (int*)malloc(n * sizeof(int));
        printf("Enter %d sorted elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        int result_size;
        int *result = two_sum_optimized(arr, n, target, &result_size);
        
        if (result) {
            printf("Pair found at indices: %d, %d\n", result[0], result[1]);
            free(result);
        } else {
            printf("No pair found\n");
        }
        
        free(arr);
        
    } else if (choice == 4) {
        int n, k;
        printf("Enter array size and window size: ");
        scanf("%d %d", &n, &k);
        
        int *arr = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        int max_sum = max_sum_subarray_k(arr, n, k);
        printf("Maximum sum of subarray of size %d: %d\n", k, max_sum);
        
        free(arr);
        
    } else if (choice == 5) {
        int n, q;
        printf("Enter array size and number of queries: ");
        scanf("%d %d", &n, &q);
        
        int *arr = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        struct PrefixSum *ps = create_prefix_sum(arr, n);
        
        printf("Enter %d range queries (left right):\n", q);
        for (int i = 0; i < q; i++) {
            int left, right;
            scanf("%d %d", &left, &right);
            printf("Sum of range [%d, %d]: %d\n", left, right, 
                   range_sum_query(ps, left, right));
        }
        
        free(arr);
        free(ps->prefix);
        free(ps);
        
    } else if (choice == 6) {
        int n;
        printf("Enter a number: ");
        scanf("%d", &n);
        
        printf("Number: %d\n", n);
        printf("Set bits: %d\n", count_set_bits(n));
        printf("Is power of 2: %s\n", is_power_of_two(n) ? "Yes" : "No");
        printf("Multiply by 4 (2^2): %d\n", multiply_by_power_of_two(n, 2));
        printf("Divide by 8 (2^3): %d\n", divide_by_power_of_two(n, 3));
        
    } else if (choice == 7) {
        int a, b;
        printf("Enter two numbers: ");
        scanf("%d %d", &a, &b);
        
        printf("GCD using binary algorithm: %d\n", gcd_binary(a, b));
        
    } else if (choice == 8) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *arr = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        long long sum = sum_array_unrolled(arr, n);
        printf("Sum using loop unrolling: %lld\n", sum);
        
        free(arr);
        
    } else if (choice == 9) {
        printf("Memory Pool Demo:\n");
        
        struct MemoryPool *pool = create_memory_pool(sizeof(int), 10);
        
        // Allocate some blocks
        int *ptr1 = (int*)pool_alloc(pool);
        int *ptr2 = (int*)pool_alloc(pool);
        
        if (ptr1 && ptr2) {
            *ptr1 = 42;
            *ptr2 = 84;
            printf("Allocated and set values: %d, %d\n", *ptr1, *ptr2);
            
            // Free the blocks
            pool_free(pool, ptr1);
            pool_free(pool, ptr2);
            printf("Freed the blocks\n");
        }
        
        free(pool->pool);
        free(pool->free_list);
        free(pool);
        
    } else if (choice == 10) {
        benchmark_fibonacci();
    }
    
    return 0;
}