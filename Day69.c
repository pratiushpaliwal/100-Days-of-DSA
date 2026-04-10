/*
 * Day 69 - Dijkstra's Algorithm (Shortest Path)
 *
 * Problem: Given weighted graph with non-negative edges, compute shortest
 *          path from source using priority queue.
 *
 * Time Complexity: O(E log V)
 * Space Complexity: O(V + E)
 */

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

struct Edge {
    int to;
    int weight;
    struct Edge* next;
};

struct Edge* addEdge(struct Edge* head, int to, int weight) {
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = NULL;

    if(head == NULL)
        return newEdge;

    struct Edge* temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = newEdge;
    return head;
}

void dijkstra(int V, struct Edge* adj[], int source) {
    int dist[V];
    int visited[V];
    
    for(int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    
    dist[source] = 0;
    
    for(int count = 0; count < V; count++) {
        /* Find unvisited vertex with minimum distance */
        int u = -1;
        for(int i = 0; i < V; i++) {
            if(!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        
        if(u == -1 || dist[u] == INF)
            break;
        
        visited[u] = 1;
        
        /* Relax adjacent edges */
        struct Edge* temp = adj[u];
        while(temp != NULL) {
            int v = temp->to;
            int w = temp->weight;
            
            if(!visited[v] && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
            
            temp = temp->next;
        }
    }
    
    printf("Shortest distances from source %d:\n", source);
    for(int i = 0; i < V; i++) {
        if(dist[i] == INF)
            printf("Vertex %d: INF\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    
    struct Edge* adj[V];
    for(int i = 0; i < V; i++)
        adj[i] = NULL;
    
    printf("Enter edges (u v weight):\n");
    for(int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u] = addEdge(adj[u], v, w);
        adj[v] = addEdge(adj[v], u, w); /* Undirected graph */
    }
    
    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);
    
    dijkstra(V, adj, source);
    
    return 0;
}
