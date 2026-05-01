// Day 95: Problem Solving - Mixed Practice
// Problem: Advanced Problem Solving Techniques

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 1005

// Problem 1: Longest Increasing Subsequence with Binary Search
int lis_binary_search(int arr[], int n) {
    int *tails = (int*)malloc(n * sizeof(int));
    int size = 0;
    
    for (int i = 0; i < n; i++) {
        // Binary search for position to insert arr[i]
        int left = 0, right = size;
        while (left < right) {
            int mid = (left + right) / 2;
            if (tails[mid] < arr[i]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        tails[left] = arr[i];
        if (left == size) {
            size++;
        }
    }
    
    free(tails);
    return size;
}

// Problem 2: Maximum Subarray Sum with Kadane's Algorithm
long long max_subarray_sum(int arr[], int n) {
    long long max_so_far = arr[0];
    long long max_ending_here = arr[0];
    
    for (int i = 1; i < n; i++) {
        max_ending_here = (arr[i] > max_ending_here + arr[i]) ? 
                         arr[i] : max_ending_here + arr[i];
        max_so_far = (max_so_far > max_ending_here) ? 
                     max_so_far : max_ending_here;
    }
    
    return max_so_far;
}

// Problem 3: Edit Distance (Levenshtein Distance)
int edit_distance(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    int **dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
    }
    
    // Initialize base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    
    // Fill DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + ((dp[i-1][j] < dp[i][j-1]) ? 
                              (dp[i-1][j] < dp[i-1][j-1] ? dp[i-1][j] : dp[i-1][j-1]) :
                              (dp[i][j-1] < dp[i-1][j-1] ? dp[i][j-1] : dp[i-1][j-1]));
            }
        }
    }
    
    int result = dp[m][n];
    
    // Free memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// Problem 4: 0/1 Knapsack Problem
int knapsack_01(int weights[], int values[], int n, int capacity) {
    int **dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)calloc(capacity + 1, sizeof(int));
    }
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                dp[i][w] = (values[i-1] + dp[i-1][w - weights[i-1]] > dp[i-1][w]) ?
                           values[i-1] + dp[i-1][w - weights[i-1]] : dp[i-1][w];
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    int result = dp[n][capacity];
    
    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// Problem 5: Coin Change - Minimum Coins
int coin_change_min(int coins[], int n, int amount) {
    int *dp = (int*)malloc((amount + 1) * sizeof(int));
    
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }
    
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                dp[i] = (dp[i] < dp[i - coins[j]] + 1) ? dp[i] : dp[i - coins[j]] + 1;
            }
        }
    }
    
    int result = (dp[amount] == INT_MAX) ? -1 : dp[amount];
    free(dp);
    return result;
}

// Problem 6: Longest Common Subsequence
int lcs_length(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    int **dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)calloc(n + 1, sizeof(int));
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }
    
    int result = dp[m][n];
    
    // Free memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// Problem 7: Matrix Chain Multiplication
int matrix_chain_order(int dimensions[], int n) {
    int **dp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)calloc(n, sizeof(int));
    }
    
    // l is chain length
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k+1][j] + 
                          dimensions[i-1] * dimensions[k] * dimensions[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }
    
    int result = dp[1][n-1];
    
    // Free memory
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// Problem 8: Maximum Product Subarray
long long max_product_subarray(int arr[], int n) {
    long long max_so_far = arr[0];
    long long min_so_far = arr[0];
    long long result = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) {
            // Swap max and min
            long long temp = max_so_far;
            max_so_far = min_so_far;
            min_so_far = temp;
        }
        
        max_so_far = (arr[i] > max_so_far * arr[i]) ? arr[i] : max_so_far * arr[i];
        min_so_far = (arr[i] < min_so_far * arr[i]) ? arr[i] : min_so_far * arr[i];
        
        result = (result > max_so_far) ? result : max_so_far;
    }
    
    return result;
}

// Problem 9: Palindrome Partitioning - Minimum Cuts
int min_palindrome_cuts(char *str) {
    int n = strlen(str);
    
    // Create palindrome table
    int **is_palindrome = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        is_palindrome[i] = (int*)calloc(n, sizeof(int));
    }
    
    // Fill palindrome table
    for (int i = 0; i < n; i++) {
        is_palindrome[i][i] = 1;
    }
    
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            if (l == 2) {
                is_palindrome[i][j] = (str[i] == str[j]);
            } else {
                is_palindrome[i][j] = (str[i] == str[j]) && is_palindrome[i+1][j-1];
            }
        }
    }
    
    // Calculate minimum cuts
    int *cuts = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        if (is_palindrome[0][i]) {
            cuts[i] = 0;
        } else {
            cuts[i] = INT_MAX;
            for (int j = 0; j < i; j++) {
                if (is_palindrome[j+1][i] && cuts[j] + 1 < cuts[i]) {
                    cuts[i] = cuts[j] + 1;
                }
            }
        }
    }
    
    int result = cuts[n-1];
    
    // Free memory
    for (int i = 0; i < n; i++) {
        free(is_palindrome[i]);
    }
    free(is_palindrome);
    free(cuts);
    
    return result;
}

// Problem 10: Word Break Problem
int word_break(char *str, char **dictionary, int dict_size) {
    int n = strlen(str);
    int *dp = (int*)calloc(n + 1, sizeof(int));
    dp[0] = 1;  // Empty string can always be segmented
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j]) {
                // Check if substring str[j...i-1] is in dictionary
                char substr[256];
                strncpy(substr, str + j, i - j);
                substr[i - j] = '\0';
                
                for (int k = 0; k < dict_size; k++) {
                    if (strcmp(substr, dictionary[k]) == 0) {
                        dp[i] = 1;
                        break;
                    }
                }
                
                if (dp[i]) break;
            }
        }
    }
    
    int result = dp[n];
    free(dp);
    return result;
}

int main() {
    printf("Choose a problem to solve:\n");
    printf("1. Longest Increasing Subsequence\n");
    printf("2. Maximum Subarray Sum\n");
    printf("3. Edit Distance\n");
    printf("4. 0/1 Knapsack\n");
    printf("5. Coin Change (Minimum Coins)\n");
    printf("6. Longest Common Subsequence\n");
    printf("7. Matrix Chain Multiplication\n");
    printf("8. Maximum Product Subarray\n");
    printf("9. Palindrome Partitioning\n");
    printf("10. Word Break\n");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *arr = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        int lis_len = lis_binary_search(arr, n);
        printf("Length of Longest Increasing Subsequence: %d\n", lis_len);
        
        free(arr);
        
    } else if (choice == 2) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *arr = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        long long max_sum = max_subarray_sum(arr, n);
        printf("Maximum Subarray Sum: %lld\n", max_sum);
        
        free(arr);
        
    } else if (choice == 3) {
        char str1[1000], str2[1000];
        printf("Enter first string: ");
        scanf("%s", str1);
        printf("Enter second string: ");
        scanf("%s", str2);
        
        int distance = edit_distance(str1, str2);
        printf("Edit Distance: %d\n", distance);
        
    } else if (choice == 4) {
        int n, capacity;
        printf("Enter number of items and knapsack capacity: ");
        scanf("%d %d", &n, &capacity);
        
        int *weights = (int*)malloc(n * sizeof(int));
        int *values = (int*)malloc(n * sizeof(int));
        
        printf("Enter weights: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &weights[i]);
        }
        
        printf("Enter values: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &values[i]);
        }
        
        int max_value = knapsack_01(weights, values, n, capacity);
        printf("Maximum value: %d\n", max_value);
        
        free(weights);
        free(values);
        
    } else if (choice == 5) {
        int n, amount;
        printf("Enter number of coin types and target amount: ");
        scanf("%d %d", &n, &amount);
        
        int *coins = (int*)malloc(n * sizeof(int));
        printf("Enter coin denominations: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &coins[i]);
        }
        
        int min_coins = coin_change_min(coins, n, amount);
        if (min_coins == -1) {
            printf("Cannot make the amount with given coins\n");
        } else {
            printf("Minimum coins needed: %d\n", min_coins);
        }
        
        free(coins);
        
    } else if (choice == 6) {
        char str1[1000], str2[1000];
        printf("Enter first string: ");
        scanf("%s", str1);
        printf("Enter second string: ");
        scanf("%s", str2);
        
        int lcs_len = lcs_length(str1, str2);
        printf("Length of Longest Common Subsequence: %d\n", lcs_len);
        
    } else if (choice == 7) {
        int n;
        printf("Enter number of matrices: ");
        scanf("%d", &n);
        
        int *dimensions = (int*)malloc((n + 1) * sizeof(int));
        printf("Enter %d dimensions: ", n + 1);
        for (int i = 0; i <= n; i++) {
            scanf("%d", &dimensions[i]);
        }
        
        int min_multiplications = matrix_chain_order(dimensions, n + 1);
        printf("Minimum scalar multiplications: %d\n", min_multiplications);
        
        free(dimensions);
        
    } else if (choice == 8) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *arr = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        long long max_product = max_product_subarray(arr, n);
        printf("Maximum Product Subarray: %lld\n", max_product);
        
        free(arr);
        
    } else if (choice == 9) {
        char str[1000];
        printf("Enter string: ");
        scanf("%s", str);
        
        int min_cuts = min_palindrome_cuts(str);
        printf("Minimum cuts for palindrome partitioning: %d\n", min_cuts);
        
    } else if (choice == 10) {
        char str[1000];
        int dict_size;
        
        printf("Enter string: ");
        scanf("%s", str);
        
        printf("Enter dictionary size: ");
        scanf("%d", &dict_size);
        
        char **dictionary = (char**)malloc(dict_size * sizeof(char*));
        printf("Enter dictionary words:\n");
        for (int i = 0; i < dict_size; i++) {
            dictionary[i] = (char*)malloc(100 * sizeof(char));
            scanf("%s", dictionary[i]);
        }
        
        int can_break = word_break(str, dictionary, dict_size);
        if (can_break) {
            printf("String can be segmented using dictionary words\n");
        } else {
            printf("String cannot be segmented using dictionary words\n");
        }
        
        for (int i = 0; i < dict_size; i++) {
            free(dictionary[i]);
        }
        free(dictionary);
    }
    
    return 0;
}