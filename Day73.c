/*
 * Day 73 - First Non-Repeating Character
 *
 * Problem: Given a string s consisting of lowercase English letters, find and
 *          return the first character that does not repeat in the string.
 *          If all characters repeat, return '$'.
 *
 * Input Format:
 * - A single string s.
 *
 * Output Format:
 * - Print the first non-repeating character or '$' if none exists.
 *
 * Sample Input:
 * geeksforgeeks
 *
 * Sample Output:
 * f
 *
 * Explanation:
 * The character 'f' occurs only once in the string and appears before any
 * other non-repeating character.
 */

#include <stdio.h>
#include <string.h>

int main() {
    char s[1000];
    int freq[26] = {0};
    int found = 0;

    printf("Enter a string: ");
    scanf("%s", s);

    /* First pass: count frequency of each character */
    for(int i = 0; s[i] != '\0'; i++) {
        freq[s[i] - 'a']++;
    }

    /* Second pass: find first character with frequency 1 */
    for(int i = 0; s[i] != '\0'; i++) {
        if(freq[s[i] - 'a'] == 1) {
            printf("%c\n", s[i]);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("$\n");

    return 0;
}
