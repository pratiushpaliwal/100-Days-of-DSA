// Day 97: Problem Solving - Interview Questions
// Problem: Common Technical Interview Problems

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 1005

// Problem 1: Two Sum - Find pair with given sum
int* two_sum(int nums[], int n, int target, int* return_size) {
    int *result = (int*)malloc(2 * sizeof(int));
    *return_size = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                *return_size = 2;
                return result;
            }
        }
    }
    
    free(result);
    return NULL;
}

// Problem 2: Valid Parentheses
int is_valid_parentheses(char* s) {
    int n = strlen(s);
    char *stack = (char*)malloc(n * sizeof(char));
    int top = -1;
    
    for (int i = 0; i < n; i++) {
        char c = s[i];
        
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } else {
            if (top == -1) {
                free(stack);
                return 0;
            }
            
            char last = stack[top--];
            if ((c == ')' && last != '(') ||
                (c == ']' && last != '[') ||
                (c == '}' && last != '{')) {
                free(stack);
                return 0;
            }
        }
    }
    
    int result = (top == -1);
    free(stack);
    return result;
}

// Problem 3: Merge Two Sorted Arrays
void merge_sorted_arrays(int nums1[], int m, int nums2[], int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }
    
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

// Problem 4: Remove Duplicates from Sorted Array
int remove_duplicates(int nums[], int n) {
    if (n <= 1) return n;
    
    int write_index = 1;
    
    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[i - 1]) {
            nums[write_index++] = nums[i];
        }
    }
    
    return write_index;
}

// Problem 5: Rotate Array
void reverse_array(int nums[], int start, int end) {
    while (start < end) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

void rotate_array(int nums[], int n, int k) {
    k %= n;
    reverse_array(nums, 0, n - 1);
    reverse_array(nums, 0, k - 1);
    reverse_array(nums, k, n - 1);
}

// Problem 6: Best Time to Buy and Sell Stock
int max_profit_stock(int prices[], int n) {
    if (n <= 1) return 0;
    
    int min_price = prices[0];
    int max_profit = 0;
    
    for (int i = 1; i < n; i++) {
        if (prices[i] < min_price) {
            min_price = prices[i];
        } else if (prices[i] - min_price > max_profit) {
            max_profit = prices[i] - min_price;
        }
    }
    
    return max_profit;
}

// Problem 7: Contains Duplicate
int contains_duplicate(int nums[], int n) {
    // Simple O(n²) solution for interview
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] == nums[j]) {
                return 1;
            }
        }
    }
    return 0;
}

// Problem 8: Product of Array Except Self
int* product_except_self(int nums[], int n, int* return_size) {
    int *result = (int*)malloc(n * sizeof(int));
    *return_size = n;
    
    // Left products
    result[0] = 1;
    for (int i = 1; i < n; i++) {
        result[i] = result[i - 1] * nums[i - 1];
    }
    
    // Right products
    int right = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= right;
        right *= nums[i];
    }
    
    return result;
}

// Problem 9: Maximum Subarray (Kadane's Algorithm)
int max_subarray(int nums[], int n) {
    int max_so_far = nums[0];
    int max_ending_here = nums[0];
    
    for (int i = 1; i < n; i++) {
        max_ending_here = (nums[i] > max_ending_here + nums[i]) ? 
                         nums[i] : max_ending_here + nums[i];
        max_so_far = (max_so_far > max_ending_here) ? 
                     max_so_far : max_ending_here;
    }
    
    return max_so_far;
}

// Problem 10: 3Sum - Find triplets that sum to zero
int** three_sum(int nums[], int n, int* return_size, int** return_column_sizes) {
    *return_size = 0;
    if (n < 3) return NULL;
    
    // Sort array first (simple bubble sort for interview)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
    
    int **result = (int**)malloc(n * n * sizeof(int*));
    *return_column_sizes = (int*)malloc(n * n * sizeof(int));
    
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // Skip duplicates
        
        int left = i + 1, right = n - 1;
        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            if (sum == 0) {
                result[*return_size] = (int*)malloc(3 * sizeof(int));
                result[*return_size][0] = nums[i];
                result[*return_size][1] = nums[left];
                result[*return_size][2] = nums[right];
                (*return_column_sizes)[*return_size] = 3;
                (*return_size)++;
                
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}

// Problem 11: Group Anagrams
int are_anagrams(char *str1, char *str2) {
    if (strlen(str1) != strlen(str2)) return 0;
    
    int count[26] = {0};
    
    for (int i = 0; str1[i]; i++) {
        count[str1[i] - 'a']++;
        count[str2[i] - 'a']--;
    }
    
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) return 0;
    }
    
    return 1;
}

// Problem 12: Valid Anagram
int is_anagram(char* s, char* t) {
    return are_anagrams(s, t);
}

// Problem 13: Climbing Stairs (Fibonacci variant)
int climb_stairs(int n) {
    if (n <= 2) return n;
    
    int prev2 = 1, prev1 = 2;
    
    for (int i = 3; i <= n; i++) {
        int current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

// Problem 14: House Robber
int rob_houses(int nums[], int n) {
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    int prev2 = nums[0];
    int prev1 = (nums[0] > nums[1]) ? nums[0] : nums[1];
    
    for (int i = 2; i < n; i++) {
        int current = (prev1 > prev2 + nums[i]) ? prev1 : prev2 + nums[i];
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

// Problem 15: Reverse Linked List (using array simulation)
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverse_list(struct ListNode* head) {
    struct ListNode *prev = NULL;
    struct ListNode *current = head;
    
    while (current != NULL) {
        struct ListNode *next_temp = current->next;
        current->next = prev;
        prev = current;
        current = next_temp;
    }
    
    return prev;
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("Choose an interview problem:\n");
    printf("1. Two Sum\n");
    printf("2. Valid Parentheses\n");
    printf("3. Merge Sorted Arrays\n");
    printf("4. Remove Duplicates\n");
    printf("5. Rotate Array\n");
    printf("6. Best Time to Buy/Sell Stock\n");
    printf("7. Contains Duplicate\n");
    printf("8. Product of Array Except Self\n");
    printf("9. Maximum Subarray\n");
    printf("10. 3Sum\n");
    printf("11. Valid Anagram\n");
    printf("12. Climbing Stairs\n");
    printf("13. House Robber\n");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        int n, target;
        printf("Enter array size and target: ");
        scanf("%d %d", &n, &target);
        
        int *nums = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
        
        int return_size;
        int *result = two_sum(nums, n, target, &return_size);
        
        if (result) {
            printf("Indices: %d, %d\n", result[0], result[1]);
            free(result);
        } else {
            printf("No solution found\n");
        }
        
        free(nums);
        
    } else if (choice == 2) {
        char s[1000];
        printf("Enter string with parentheses: ");
        scanf("%s", s);
        
        if (is_valid_parentheses(s)) {
            printf("Valid parentheses\n");
        } else {
            printf("Invalid parentheses\n");
        }
        
    } else if (choice == 3) {
        int m, n;
        printf("Enter sizes of two arrays: ");
        scanf("%d %d", &m, &n);
        
        int *nums1 = (int*)malloc((m + n) * sizeof(int));
        int *nums2 = (int*)malloc(n * sizeof(int));
        
        printf("Enter %d elements of first array: ", m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &nums1[i]);
        }
        
        printf("Enter %d elements of second array: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums2[i]);
        }
        
        merge_sorted_arrays(nums1, m, nums2, n);
        
        printf("Merged array: ");
        print_array(nums1, m + n);
        
        free(nums1);
        free(nums2);
        
    } else if (choice == 4) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *nums = (int*)malloc(n * sizeof(int));
        printf("Enter %d sorted elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
        
        int new_length = remove_duplicates(nums, n);
        printf("Array after removing duplicates: ");
        print_array(nums, new_length);
        printf("New length: %d\n", new_length);
        
        free(nums);
        
    } else if (choice == 5) {
        int n, k;
        printf("Enter array size and rotation count: ");
        scanf("%d %d", &n, &k);
        
        int *nums = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
        
        printf("Original array: ");
        print_array(nums, n);
        
        rotate_array(nums, n, k);
        
        printf("After rotating by %d: ", k);
        print_array(nums, n);
        
        free(nums);
        
    } else if (choice == 6) {
        int n;
        printf("Enter number of days: ");
        scanf("%d", &n);
        
        int *prices = (int*)malloc(n * sizeof(int));
        printf("Enter %d stock prices: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &prices[i]);
        }
        
        int profit = max_profit_stock(prices, n);
        printf("Maximum profit: %d\n", profit);
        
        free(prices);
        
    } else if (choice == 7) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *nums = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
        
        if (contains_duplicate(nums, n)) {
            printf("Array contains duplicates\n");
        } else {
            printf("Array does not contain duplicates\n");
        }
        
        free(nums);
        
    } else if (choice == 8) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *nums = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
        
        int return_size;
        int *result = product_except_self(nums, n, &return_size);
        
        printf("Product except self: ");
        print_array(result, return_size);
        
        free(nums);
        free(result);
        
    } else if (choice == 9) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *nums = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
        
        int max_sum = max_subarray(nums, n);
        printf("Maximum subarray sum: %d\n", max_sum);
        
        free(nums);
        
    } else if (choice == 10) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        
        int *nums = (int*)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
        
        int return_size;
        int *return_column_sizes;
        int **result = three_sum(nums, n, &return_size, &return_column_sizes);
        
        printf("Triplets that sum to zero:\n");
        for (int i = 0; i < return_size; i++) {
            printf("[%d, %d, %d]\n", result[i][0], result[i][1], result[i][2]);
            free(result[i]);
        }
        
        if (return_size == 0) {
            printf("No triplets found\n");
        }
        
        free(nums);
        free(result);
        free(return_column_sizes);
        
    } else if (choice == 11) {
        char s[1000], t[1000];
        printf("Enter two strings: ");
        scanf("%s %s", s, t);
        
        if (is_anagram(s, t)) {
            printf("Strings are anagrams\n");
        } else {
            printf("Strings are not anagrams\n");
        }
        
    } else if (choice == 12) {
        int n;
        printf("Enter number of stairs: ");
        scanf("%d", &n);
        
        int ways = climb_stairs(n);
        printf("Number of ways to climb %d stairs: %d\n", n, ways);
        
    } else if (choice == 13) {
        int n;
        printf("Enter number of houses: ");
        scanf("%d", &n);
        
        int *money = (int*)malloc(n * sizeof(int));
        printf("Enter money in each house: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &money[i]);
        }
        
        int max_money = rob_houses(money, n);
        printf("Maximum money that can be robbed: %d\n", max_money);
        
        free(money);
    }
    
    return 0;
}