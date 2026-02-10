//Problem: Read a string and check if it is a palindrome using two-pointer comparison.


#include <stdio.h>
#include <string.h>

int main() {
    char arr[256];
    scanf("%s", arr);
    int len = strlen(arr);
    int j;
    for (int i = 0; i < len; i++) {
        j = len - i - 1;
        if (arr[i] != arr[j]) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
