/*
 * Day 77 - Check if Graph is Connected
 *
 * Problem: Using BFS or DFS, check if the entire graph is connected.
 *
 * Input Format:
 * n m
 * edges
 *
 * Output Format:
 * CONNECTED
 * NOT CONNECTED
 *
 * Sample Input:
 * 4 2
 * 1 2
 * 3 4
 *
 * Sample Output:
 * NOT CONNECTED
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
    dfs(1, adj, visited);

    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            printf("NOT CONNECTED\n");
            return 0;
        }
    }

    printf("CONNECTED\n");
    return 0;
}
