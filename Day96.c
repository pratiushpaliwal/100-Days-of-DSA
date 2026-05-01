// Day 96: Problem Solving - Contest Problems
// Problem: Competitive Programming Style Problems

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAXN 100005
#define MOD 1000000007

// Problem 1: Fast Exponentiation with Modulo
long long fast_power(long long base, long long exp, long long mod) {
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

// Problem 2: Sieve of Eratosthenes for Prime Generation
void sieve_of_eratosthenes(int n, int primes[]) {
    int *is_prime = (int*)malloc((n + 1) * sizeof(int));
    
    for (int i = 0; i <= n; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;
    
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes[count++] = i;
        }
    }
    primes[count] = -1;  // Sentinel
    
    free(is_prime);
}

// Problem 3: GCD and LCM using Euclidean Algorithm
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        long long temp = a;
        a = b;
        b = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

// Problem 4: Modular Inverse using Extended Euclidean Algorithm
long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    
    long long x1, y1;
    long long gcd_val = extended_gcd(b % a, a, &x1, &y1);
    
    *x = y1 - (b / a) * x1;
    *y = x1;
    
    return gcd_val;
}

long long mod_inverse(long long a, long long m) {
    long long x, y;
    long long gcd_val = extended_gcd(a, m, &x, &y);
    
    if (gcd_val != 1) {
        return -1;  // Modular inverse doesn't exist
    }
    
    return (x % m + m) % m;
}

// Problem 5: Fibonacci with Matrix Exponentiation
void matrix_multiply(long long F[2][2], long long M[2][2]) {
    long long x = (F[0][0] * M[0][0] + F[0][1] * M[1][0]) % MOD;
    long long y = (F[0][0] * M[0][1] + F[0][1] * M[1][1]) % MOD;
    long long z = (F[1][0] * M[0][0] + F[1][1] * M[1][0]) % MOD;
    long long w = (F[1][0] * M[0][1] + F[1][1] * M[1][1]) % MOD;
    
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void matrix_power(long long F[2][2], long long n) {
    if (n == 0 || n == 1) return;
    
    long long M[2][2] = {{1, 1}, {1, 0}};
    
    matrix_power(F, n / 2);
    matrix_multiply(F, F);
    
    if (n % 2 != 0) {
        matrix_multiply(F, M);
    }
}

long long fibonacci_fast(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    long long F[2][2] = {{1, 1}, {1, 0}};
    matrix_power(F, n - 1);
    
    return F[0][0];
}

// Problem 6: Counting Inversions using Merge Sort
long long merge_and_count(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    long long inv_count = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
    
    return inv_count;
}

long long merge_sort_and_count(int arr[], int temp[], int left, int right) {
    long long inv_count = 0;
    
    if (left < right) {
        int mid = (left + right) / 2;
        
        inv_count += merge_sort_and_count(arr, temp, left, mid);
        inv_count += merge_sort_and_count(arr, temp, mid + 1, right);
        inv_count += merge_and_count(arr, temp, left, mid, right);
    }
    
    return inv_count;
}

// Problem 7: Next Greater Element using Stack
void next_greater_element(int arr[], int n, int result[]) {
    int *stack = (int*)malloc(n * sizeof(int));
    int top = -1;
    
    // Initialize result array
    for (int i = 0; i < n; i++) {
        result[i] = -1;
    }
    
    for (int i = 0; i < n; i++) {
        while (top >= 0 && arr[stack[top]] < arr[i]) {
            result[stack[top]] = arr[i];
            top--;
        }
        stack[++top] = i;
    }
    
    free(stack);
}

// Problem 8: Sliding Window Maximum using Deque
void sliding_window_maximum(int arr[], int n, int k, int result[]) {
    int *deque = (int*)malloc(n * sizeof(int));
    int front = 0, rear = -1;
    
    for (int i = 0; i < n; i++) {
        // Remove elements outside current window
        while (front <= rear && deque[front] <= i - k) {
            front++;
        }
        
        // Remove elements smaller than current element
        while (front <= rear && arr[deque[rear]] <= arr[i]) {
            rear--;
        }
        
        deque[++rear] = i;
        
        // Store result for current window
        if (i >= k - 1) {
            result[i - k + 1] = arr[deque[front]];
        }
    }
    
    free(deque);
}

// Problem 9: Longest Palindromic Substring (Manacher's Algorithm)
char* longest_palindrome_manacher(char *s) {
    int n = strlen(s);
    if (n == 0) return "";
    
    // Transform string: "abc" -> "^#a#b#c#$"
    char *T = (char*)malloc((2 * n + 4) * sizeof(char));
    T[0] = '^';
    for (int i = 0; i < n; i++) {
        T[2 * i + 1] = '#';
        T[2 * i + 2] = s[i];
    }
    T[2 * n + 1] = '#';
    T[2 * n + 2] = '$';
    T[2 * n + 3] = '\0';
    
    int m = 2 * n + 3;
    int *P = (int*)calloc(m, sizeof(int));
    int center = 0, right = 0;
    int max_len = 0, center_index = 0;
    
    for (int i = 1; i < m - 1; i++) {
        int mirror = 2 * center - i;
        
        if (i < right) {
            P[i] = (right - i < P[mirror]) ? right - i : P[mirror];
        }
        
        // Try to expand palindrome centered at i
        while (T[i + P[i] + 1] == T[i - P[i] - 1]) {
            P[i]++;
        }
        
        // If palindrome centered at i extends past right, adjust center and right
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
        
        // Update maximum length palindrome
        if (P[i] > max_len) {
            max_len = P[i];
            center_index = i;
        }
    }
    
    // Extract the longest palindrome
    int start = (center_index - max_len) / 2;
    char *result = (char*)malloc((max_len + 1) * sizeof(char));
    strncpy(result, s + start, max_len);
    result[max_len] = '\0';
    
    free(T);
    free(P);
    return result;
}

// Problem 10: Maximum Flow (Ford-Fulkerson with DFS)
int **capacity, **flow;
int *visited;

int dfs_max_flow(int u, int sink, int pushed) {
    if (u == sink) return pushed;
    
    visited[u] = 1;
    
    for (int v = 0; v < MAXN; v++) {
        if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
            int delta = dfs_max_flow(v, sink, 
                       (pushed < capacity[u][v] - flow[u][v]) ? 
                       pushed : capacity[u][v] - flow[u][v]);
            
            if (delta > 0) {
                flow[u][v] += delta;
                flow[v][u] -= delta;
                return delta;
            }
        }
    }
    
    return 0;
}

int max_flow_ford_fulkerson(int source, int sink, int n) {
    int total_flow = 0;
    
    while (1) {
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
        }
        
        int pushed = dfs_max_flow(source, sink, INT_MAX);
        if (pushed == 0) break;
        
        total_flow += pushed;
    }
    
    return total_flow;
}

int main() {
    printf("Choose a contest problem:\n");
    printf("1. Fast Exponentiation\n");
    printf("2. Prime Generation (Sieve)\n");
    printf("3. GCD and LCM\n");
    printf("4. Modular Inverse\n");
    printf("5. Fast Fibonacci\n");
    printf("6. Count Inversions\n");
    printf("7. Next Greater Element\n");
    printf("8. Sliding Window Maximum\n");
    printf("9. Longest Palindromic Substring\n");
    printf("10. Maximum Flow\n");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        long long base, exp, mod;
        printf("Enter base, exponent, and modulo: ");
        scanf("%lld %lld %lld", &base, &exp, &mod);
        
        long long result = fast_power(base, exp, mod);
        printf("%lld^%lld mod %lld = %lld\n", base, exp, mod, result);
        
    } else if (choice == 2) {
        int n;
        printf("Enter upper limit: ");
        scanf("%d", &n);
        
        int *primes = (int*)malloc((n + 1) * sizeof(int));
        sieve_of_eratosthenes(n, primes);
        
        printf("Primes up to %d: ", n);
        for (int i = 0; primes[i] != -1; i++) {
            printf("%d ", primes[i]);
        }
        printf("\n");
        
        free(primes);
        
    } else if (choice == 3) {
        long long a, b;
        printf("Enter two numbers: ");
        scanf("%lld %lld", &a, &b);
        
        printf("GCD(%lld, %lld) = %lld\n", a, b, gcd(a, b));
        printf("LCM(%lld, %lld) = %lld\n", a, b, lcm(a, b));
        
    } else if (choice == 4) {
        long long a, m;
        printf("Enter number and modulo: ");
        scanf("%lld %lld", &a, &m);
        
        long long inv = mod_inverse(a, m);
        if (inv == -1) {
            printf("Modular inverse doesn't exist\n");
        } else {
            printf("Modular inverse of %lld mod %lld = %lld\n", a, m, inv);
        }
        
    } else if (choice == 5) {
        long long n;
        printf("Enter n for Fibonacci: ");
        scanf("%lld", &n);
        
        long long fib = fibonacci_fast(n);
        printf("Fibonacci(%lld) = %lld\n", n, fib);
        
    } else if (choice == 6) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *arr = (int*)malloc(n * sizeof(int));
        int *temp = (int*)malloc(n * sizeof(int));
        
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        long long inversions = merge_sort_and_count(arr, temp, 0, n - 1);
        printf("Number of inversions: %lld\n", inversions);
        
        free(arr);
        free(temp);
        
    } else if (choice == 7) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *arr = (int*)malloc(n * sizeof(int));
        int *result = (int*)malloc(n * sizeof(int));
        
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        next_greater_element(arr, n, result);
        
        printf("Next greater elements: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        
        free(arr);
        free(result);
        
    } else if (choice == 8) {
        int n, k;
        printf("Enter array size and window size: ");
        scanf("%d %d", &n, &k);
        
        int *arr = (int*)malloc(n * sizeof(int));
        int *result = (int*)malloc((n - k + 1) * sizeof(int));
        
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        sliding_window_maximum(arr, n, k, result);
        
        printf("Sliding window maximums: ");
        for (int i = 0; i < n - k + 1; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        
        free(arr);
        free(result);
        
    } else if (choice == 9) {
        char str[1000];
        printf("Enter string: ");
        scanf("%s", str);
        
        char *longest = longest_palindrome_manacher(str);
        printf("Longest palindromic substring: %s\n", longest);
        
        free(longest);
        
    } else if (choice == 10) {
        int n, m;
        printf("Enter number of vertices and edges: ");
        scanf("%d %d", &n, &m);
        
        // Allocate memory for capacity and flow matrices
        capacity = (int**)malloc(n * sizeof(int*));
        flow = (int**)malloc(n * sizeof(int*));
        visited = (int*)malloc(n * sizeof(int));
        
        for (int i = 0; i < n; i++) {
            capacity[i] = (int*)calloc(n, sizeof(int));
            flow[i] = (int*)calloc(n, sizeof(int));
        }
        
        printf("Enter edges (u v capacity):\n");
        for (int i = 0; i < m; i++) {
            int u, v, cap;
            scanf("%d %d %d", &u, &v, &cap);
            capacity[u][v] = cap;
        }
        
        int source, sink;
        printf("Enter source and sink: ");
        scanf("%d %d", &source, &sink);
        
        int max_flow_value = max_flow_ford_fulkerson(source, sink, n);
        printf("Maximum flow: %d\n", max_flow_value);
        
        // Free memory
        for (int i = 0; i < n; i++) {
            free(capacity[i]);
            free(flow[i]);
        }
        free(capacity);
        free(flow);
        free(visited);
    }
    
    return 0;
}