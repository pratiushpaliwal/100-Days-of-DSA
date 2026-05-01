// Day 90: Advanced Algorithms - Mo's Algorithm
// Problem: Range Queries using Mo's Algorithm for frequency counting

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN 100005
#define MAXVAL 1000005

struct Query {
    int l, r, idx;
} queries[MAXN];

int arr[MAXN];
int freq[MAXVAL];
int answers[MAXN];
int current_answer = 0;
int block_size;

// Comparator for Mo's algorithm
int compare(const void *a, const void *b) {
    struct Query *qa = (struct Query *)a;
    struct Query *qb = (struct Query *)b;
    
    int block_a = qa->l / block_size;
    int block_b = qb->l / block_size;
    
    if (block_a != block_b) {
        return block_a - block_b;
    }
    
    // If in same block, sort by right endpoint
    if (block_a & 1) {
        return qa->r - qb->r;  // Odd blocks: ascending order
    } else {
        return qb->r - qa->r;  // Even blocks: descending order
    }
}

// Add element at index idx to current range
void add(int idx) {
    freq[arr[idx]]++;
    if (freq[arr[idx]] == 1) {
        current_answer++;  // New distinct element
    }
}

// Remove element at index idx from current range
void remove(int idx) {
    freq[arr[idx]]--;
    if (freq[arr[idx]] == 0) {
        current_answer--;  // Element no longer present
    }
}

// Mo's algorithm to process all queries
void mo_algorithm(int n, int q) {
    block_size = (int)sqrt(n) + 1;
    
    // Sort queries according to Mo's algorithm
    qsort(queries, q, sizeof(struct Query), compare);
    
    int curr_l = 0, curr_r = -1;
    
    for (int i = 0; i < q; i++) {
        int l = queries[i].l;
        int r = queries[i].r;
        
        // Extend or shrink current range to match query range
        while (curr_r < r) {
            curr_r++;
            add(curr_r);
        }
        
        while (curr_r > r) {
            remove(curr_r);
            curr_r--;
        }
        
        while (curr_l < l) {
            remove(curr_l);
            curr_l++;
        }
        
        while (curr_l > l) {
            curr_l--;
            add(curr_l);
        }
        
        // Store answer for this query
        answers[queries[i].idx] = current_answer;
    }
}

// Alternative problem: Range sum of squares
long long sum_of_squares = 0;
long long element_contribution[MAXVAL];

void add_square(int idx) {
    int val = arr[idx];
    sum_of_squares -= element_contribution[val];
    freq[val]++;
    element_contribution[val] = (long long)freq[val] * freq[val] * val;
    sum_of_squares += element_contribution[val];
}

void remove_square(int idx) {
    int val = arr[idx];
    sum_of_squares -= element_contribution[val];
    freq[val]--;
    element_contribution[val] = (long long)freq[val] * freq[val] * val;
    sum_of_squares += element_contribution[val];
}

void mo_algorithm_squares(int n, int q) {
    block_size = (int)sqrt(n) + 1;
    qsort(queries, q, sizeof(struct Query), compare);
    
    int curr_l = 0, curr_r = -1;
    
    for (int i = 0; i < q; i++) {
        int l = queries[i].l;
        int r = queries[i].r;
        
        while (curr_r < r) {
            curr_r++;
            add_square(curr_r);
        }
        
        while (curr_r > r) {
            remove_square(curr_r);
            curr_r--;
        }
        
        while (curr_l < l) {
            remove_square(curr_l);
            curr_l++;
        }
        
        while (curr_l > l) {
            curr_l--;
            add_square(curr_l);
        }
        
        answers[queries[i].idx] = sum_of_squares;
    }
}

int main() {
    int n, q;
    printf("Enter array size and number of queries: ");
    scanf("%d %d", &n, &q);
    
    printf("Enter %d array elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter %d queries (l r, 0-indexed): ", q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].r);
        queries[i].idx = i;
    }
    
    printf("\nChoose problem type:\n");
    printf("1. Count distinct elements in range\n");
    printf("2. Sum of squares of frequencies\n");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        mo_algorithm(n, q);
        
        printf("\nResults (distinct elements in each range):\n");
        for (int i = 0; i < q; i++) {
            printf("Query %d [%d, %d]: %d distinct elements\n", 
                   i + 1, queries[i].l, queries[i].r, answers[i]);
        }
    } else {
        // Reset for squares problem
        memset(freq, 0, sizeof(freq));
        memset(element_contribution, 0, sizeof(element_contribution));
        sum_of_squares = 0;
        
        mo_algorithm_squares(n, q);
        
        printf("\nResults (sum of squares of frequencies):\n");
        for (int i = 0; i < q; i++) {
            printf("Query %d [%d, %d]: %lld\n", 
                   i + 1, queries[i].l, queries[i].r, (long long)answers[i]);
        }
    }
    
    return 0;
}