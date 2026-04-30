// Day 89: Advanced Algorithms - Square Root Decomposition
// Problem: Range Sum Query with Updates using Square Root Decomposition

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN 100005

int arr[MAXN];
int block[MAXN];
int block_size;
int n;

// Initialize square root decomposition
void initialize(int size) {
    n = size;
    block_size = (int)sqrt(n) + 1;
    
    // Build blocks
    for (int i = 0; i < n; i++) {
        block[i / block_size] += arr[i];
    }
}

// Update element at index idx to new value
void update(int idx, int new_val) {
    int old_val = arr[idx];
    arr[idx] = new_val;
    
    // Update corresponding block
    block[idx / block_size] += (new_val - old_val);
}

// Range sum query from l to r (inclusive)
long long range_sum(int l, int r) {
    long long sum = 0;
    
    int left_block = l / block_size;
    int right_block = r / block_size;
    
    if (left_block == right_block) {
        // Both indices in same block
        for (int i = l; i <= r; i++) {
            sum += arr[i];
        }
    } else {
        // Left partial block
        for (int i = l; i < (left_block + 1) * block_size; i++) {
            sum += arr[i];
        }
        
        // Complete middle blocks
        for (int i = left_block + 1; i < right_block; i++) {
            sum += block[i];
        }
        
        // Right partial block
        for (int i = right_block * block_size; i <= r; i++) {
            sum += arr[i];
        }
    }
    
    return sum;
}

// Range update: add value to all elements in range [l, r]
void range_update(int l, int r, int val) {
    int left_block = l / block_size;
    int right_block = r / block_size;
    
    if (left_block == right_block) {
        // Both indices in same block
        for (int i = l; i <= r; i++) {
            arr[i] += val;
        }
        block[left_block] += val * (r - l + 1);
    } else {
        // Left partial block
        int left_count = (left_block + 1) * block_size - l;
        for (int i = l; i < (left_block + 1) * block_size; i++) {
            arr[i] += val;
        }
        block[left_block] += val * left_count;
        
        // Complete middle blocks
        for (int i = left_block + 1; i < right_block; i++) {
            block[i] += val * block_size;
            // Update all elements in the block
            for (int j = i * block_size; j < (i + 1) * block_size; j++) {
                arr[j] += val;
            }
        }
        
        // Right partial block
        int right_count = r - right_block * block_size + 1;
        for (int i = right_block * block_size; i <= r; i++) {
            arr[i] += val;
        }
        block[right_block] += val * right_count;
    }
}

// Find maximum element in range [l, r]
int range_max(int l, int r) {
    int max_val = arr[l];
    
    int left_block = l / block_size;
    int right_block = r / block_size;
    
    if (left_block == right_block) {
        // Both indices in same block
        for (int i = l; i <= r; i++) {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
    } else {
        // Left partial block
        for (int i = l; i < (left_block + 1) * block_size; i++) {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
        
        // Complete middle blocks
        for (int i = left_block + 1; i < right_block; i++) {
            for (int j = i * block_size; j < (i + 1) * block_size; j++) {
                if (arr[j] > max_val) {
                    max_val = arr[j];
                }
            }
        }
        
        // Right partial block
        for (int i = right_block * block_size; i <= r; i++) {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
    }
    
    return max_val;
}

void print_array() {
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("Blocks: ");
    for (int i = 0; i <= n / block_size; i++) {
        printf("%d ", block[i]);
    }
    printf("\n");
}

int main() {
    int q;
    printf("Enter array size and number of queries: ");
    scanf("%d %d", &n, &q);
    
    printf("Enter %d array elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    initialize(n);
    
    printf("\nInitial state:\n");
    print_array();
    
    printf("\nQuery types:\n");
    printf("1 idx val - Update element at index idx to val\n");
    printf("2 l r - Range sum query from l to r\n");
    printf("3 l r val - Range update: add val to all elements in [l, r]\n");
    printf("4 l r - Range maximum query from l to r\n");
    printf("5 - Print current array state\n");
    
    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);
        
        if (type == 1) {
            int idx, val;
            scanf("%d %d", &idx, &val);
            update(idx, val);
            printf("Updated arr[%d] = %d\n", idx, val);
        } else if (type == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            long long sum = range_sum(l, r);
            printf("Sum of range [%d, %d] = %lld\n", l, r, sum);
        } else if (type == 3) {
            int l, r, val;
            scanf("%d %d %d", &l, &r, &val);
            range_update(l, r, val);
            printf("Added %d to range [%d, %d]\n", val, l, r);
        } else if (type == 4) {
            int l, r;
            scanf("%d %d", &l, &r);
            int max_val = range_max(l, r);
            printf("Maximum in range [%d, %d] = %d\n", l, r, max_val);
        } else if (type == 5) {
            print_array();
        }
    }
    
    return 0;
}