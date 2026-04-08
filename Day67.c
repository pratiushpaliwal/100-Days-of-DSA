/*
 * Day 67 - Topological Sort (DFS)
 *
 * Problem: Print topological ordering of a Directed Acyclic Graph (DAG) using DFS.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
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

    if(head == NULL)
        return newNode;

    struct Node* temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    return head;
}

int stack[1000];
int top = -1;

void dfs(int node, int vis[], struct Node* adj[]) {
    vis[node] = 1;
    
    struct Node* temp = adj[node];
    while(temp != NULL) {
        int it = temp->vertex;
        if(!vis[it])
            dfs(it, vis, adj);
        temp = temp->next;
    }
    
    /* Push to stack after visiting all children */
    stack[++top] = node;
}

void topoSort(int V, struct Node* adj[]) {
    int vis[V];
    for(int i = 0; i < V; i++)
        vis[i] = 0;
    
    for(int i = 0; i < V; i++) {
        if(!vis[i])
            dfs(i, vis, adj);
    }
    
    /* Print topological order (pop from stack) */
    while(top >= 0) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    
    struct Node* adj[V];
    for(int i = 0; i < V; i++)
        adj[i] = NULL;
    
    printf("Enter directed edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u] = addNode(adj[u], v);
    }
    
    topoSort(V, adj);
    
    return 0;
}
