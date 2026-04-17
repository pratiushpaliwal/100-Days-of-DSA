/*
 * Day 76 - Count Connected Components (Undirected Graph)
 *
 * Problem: Using DFS or BFS, count number of connected components.
 *
 * Input Format:
 * n m
 * edges
 *
 * Output Format:
 * Number of connected components.
 *
 * Sample Input:
 * 6 3
 * 1 2
 * 2 3
 * 5 6
 *
 * Sample Output:
 * 3
 *
 * Explanation:
 * Components: {1,2,3}, {4}, {5,6}
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* addNode(struct Node* head, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    if(head == NULL) return newNode;
    struct Node* temp = head;
    while(temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

void dfs(int node, struct Node* adj[], int visited[]) {
    visited[node] = 1;
    struct Node* temp = adj[node];
    while(temp != NULL) {
        if(!visited[temp->vertex])
            dfs(temp->vertex, adj, visited);
        temp = temp->next;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    struct Node* adj[105] = {NULL};

    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u] = addNode(adj[u], v);
        adj[v] = addNode(adj[v], u);
    }

    int visited[105] = {0};
    int count = 0;

    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            dfs(i, adj, visited);
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
