/*
 * Day 71 - Hash Table Using Quadratic Probing
 *
 * Problem: Implement a hash table using quadratic probing with formula:
 *          h(k, i) = (h(k) + i*i) % m
 *
 * Input Format:
 * - First line: integer m (table size)
 * - Next lines: operations - INSERT x or SEARCH x
 *
 * Output Format:
 * - Result of SEARCH operations: FOUND or NOT FOUND
 *
 * Sample Input:
 * 7
 * 4
 * INSERT 49
 * INSERT 56
 * SEARCH 49
 * SEARCH 15
 *
 * Sample Output:
 * FOUND
 * NOT FOUND
 *
 * Explanation:
 * Collisions resolved using i^2 jumps.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* table;
int m;

void init() {
    for(int i = 0; i < m; i++)
        table[i] = -1;
}

void insert(int key) {
    int h = key % m;
    int i = 0;

    while(i < m) {
        int index = (h + i * i) % m;
        if(table[index] == -1) {
            table[index] = key;
            return;
        }
        i++;
    }
}

void search(int key) {
    int h = key % m;

    for(int i = 0; i < m; i++) {
        int index = (h + i * i) % m;

        if(table[index] == key) {
            printf("FOUND\n");
            return;
        }
        if(table[index] == -1) {
            printf("NOT FOUND\n");
            return;
        }
    }
    printf("NOT FOUND\n");
}

int main() {
    scanf("%d", &m);

    table = (int*)malloc(m * sizeof(int));
    init();

    int q;
    scanf("%d", &q);

    char op[10];
    int key;

    for(int i = 0; i < q; i++) {
        scanf("%s %d", op, &key);
        if(strcmp(op, "INSERT") == 0)
            insert(key);
        else if(strcmp(op, "SEARCH") == 0)
            search(key);
    }

    free(table);
    return 0;
}
