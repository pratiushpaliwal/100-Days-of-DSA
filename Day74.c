/*
 * Day 74 - Winner of an Election
 *
 * Problem: Given an array of candidate names where each name represents a vote
 *          cast for that candidate, determine the candidate who received the
 *          maximum number of votes. In case of a tie, return the
 *          lexicographically smallest candidate name.
 *
 * Input Format:
 * - First line contains an integer n representing number of votes.
 * - Second line contains n space-separated strings representing candidate names.
 *
 * Output Format:
 * - Print the name of the winning candidate followed by the number of votes received.
 *
 * Sample Input:
 * 13
 * john johnny jackie johnny john jackie jamie jamie john johnny jamie johnny john
 *
 * Sample Output:
 * john 4
 *
 * Explanation:
 * Both john and johnny receive 4 votes, but john is lexicographically smaller,
 * so john is declared the winner.
 */

#include <stdio.h>
#include <string.h>

struct Candidate {
    char name[100];
    int count;
};

int main() {
    int n;
    scanf("%d", &n);

    struct Candidate arr[1000];
    int size = 0;

    for(int i = 0; i < n; i++) {
        char temp[100];
        scanf("%s", temp);

        int found = 0;
        for(int j = 0; j < size; j++) {
            if(strcmp(arr[j].name, temp) == 0) {
                arr[j].count++;
                found = 1;
                break;
            }
        }

        if(!found) {
            strcpy(arr[size].name, temp);
            arr[size].count = 1;
            size++;
        }
    }

    char winner[100];
    int maxVotes = -1;

    for(int i = 0; i < size; i++) {
        if(arr[i].count > maxVotes) {
            maxVotes = arr[i].count;
            strcpy(winner, arr[i].name);
        }
        else if(arr[i].count == maxVotes) {
            /* Tie: choose lexicographically smaller name */
            if(strcmp(arr[i].name, winner) < 0) {
                strcpy(winner, arr[i].name);
            }
        }
    }

    printf("%s %d\n", winner, maxVotes);
    return 0;
}
