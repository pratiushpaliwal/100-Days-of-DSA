/*
 * Day 72 - First Repeated Character
 *
 * Problem: Given a string s consisting of lowercase letters, find the first
 *          repeated character. A character is considered repeated if it appears
 *          more than once, and among all such characters, the one whose second
 *          occurrence has the smallest index should be returned.
 *
 * Input Format:
 * - A single string s.
 *
 * Output Format:
 * - Print the first repeated character. If no character is repeated, print -1.
 *
 * Sample Input:
 * geeksforgeeks
 *
 * Sample Output:
 * e
 */

#include <stdio.h>
#include <string.h>

int main() {
    char s[1000];
    int freq[26] = {0};
    int found = 0;

    printf("Enter a string: ");
    scanf("%s", s);

    for(int i = 0; s[i] != '\0'; i++) {
        int idx = s[i] - 'a';
        freq[idx]++;

        if(freq[idx] == 2) {
            printf("%c\n", s[i]);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("-1\n");

    return 0;
}
