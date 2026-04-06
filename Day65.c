/*
 * Day 65 - Cycle Detection in Undirected Graph (DFS)
 *
 * Problem: Using DFS and parent tracking, detect if undirected graph has a cycle.
 *
 * Output:
 * - YES or NO
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

int dfs(int node, int parent, int vis[], struct Node* adj[]) {
    vis[node] = 1;
    struct Node* temp = adj[node];
    
    while(temp != NULL) {
        int adjacentNode = temp->vertex;
        
        if(!vis[adjacentNode]) {
            if(dfs(adjacentNode, node, vis, adj) == 1)
                return 1;
        }
        else if(adjacentNode != parent) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int isCycle(int V, struct Node* adj[]) {
    int vis[V];
    for(int i = 0; i < V; i++)
        vis[i] = 0;
    
    for(int i = 0; i < V; i++) {
        if(!vis[i]) {
            if(dfs(i, -1, vis, adj))
                return 1;
        }
    }
    return 0;
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    
    struct Node* adj[V];
    for(int i = 0; i < V; i++)
        adj[i] = NULL;
    
    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u] = addNode(adj[u], v);
        adj[v] = addNode(adj[v], u);
    }
    
    if(isCycle(V, adj))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}
