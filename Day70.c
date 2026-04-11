/*
 * Day 70 - Bellman-Ford Algorithm
 *
 * Problem: Compute shortest path from source and detect negative weight
 *          cycles using Bellman-Ford.
 *
 * Input:
 * - n vertices
 * - m edges (u, v, w)
 *
 * Output:
 * - Shortest distances OR NEGATIVE CYCLE
 *
 * Time Complexity: O(V * E)
 * Space Complexity: O(V)
 */

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    
    /* Store edges as (u, v, weight) */
    int edges[E][3];
    
    printf("Enter edges (u v weight):\n");
    for(int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }
    
    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);
    
    int dist[V];
    for(int i = 0; i < V; i++)
        dist[i] = INF;
    dist[source] = 0;
    
    /* Relax all edges V-1 times */
    for(int i = 0; i < V - 1; i++) {
        for(int j = 0; j < E; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];
            
            if(dist[u] != INF && dist[u] + wt < dist[v])
                dist[v] = dist[u] + wt;
        }
    }
    
    /* Vth relaxation to check for negative cycle */
    int negativeCycle = 0;
    for(int j = 0; j < E; j++) {
        int u = edges[j][0];
        int v = edges[j][1];
        int wt = edges[j][2];
        
        if(dist[u] != INF && dist[u] + wt < dist[v]) {
            negativeCycle = 1;
            break;
        }
    }
    
    if(negativeCycle) {
        printf("NEGATIVE CYCLE\n");
        return 0;
    }
    
    printf("Shortest distances from source %d:\n", source);
    for(int i = 0; i < V; i++) {
        if(dist[i] == INF)
            printf("Vertex %d: INF\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
    
    return 0;
}
