/*
 * Day 66 - Cycle Detection in Directed Graph
 *
 * Problem: Detect cycle in directed graph using DFS and recursion stack.
 *
 * Output:
 * - YES if cycle exists
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

int dfsCheck(int node, struct Node* adj[], int vis[], int pathVis[]) {
    vis[node] = 1;
    pathVis[node] = 1;
    
    struct Node* temp = adj[node];
    while(temp != NULL) {
        int it = temp->vertex;
        
        if(!vis[it]) {
            if(dfsCheck(it, adj, vis, pathVis) == 1)
                return 1;
        }
        else if(pathVis[it]) {
            return 1;
        }
        temp = temp->next;
    }
    
    pathVis[node] = 0;
    return 0;
}

int isCyclic(int V, struct Node* adj[]) {
    int vis[V], pathVis[V];
    for(int i = 0; i < V; i++) {
        vis[i] = 0;
        pathVis[i] = 0;
    }
    
    for(int i = 0; i < V; i++) {
        if(!vis[i]) {
            if(dfsCheck(i, adj, vis, pathVis))
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
    
    printf("Enter directed edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u] = addNode(adj[u], v);
    }
    
    if(isCyclic(V, adj))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}
