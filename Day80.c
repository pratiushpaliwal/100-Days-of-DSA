/*
 * Day 80 - Floyd-Warshall Algorithm
 *
 * Problem: Given a weighted graph with n vertices, implement the Floyd-Warshall
 *          algorithm to compute the shortest distances between every pair of
 *          vertices. The graph may contain positive or negative edge weights,
 *          but it does not contain any negative weight cycles.
 *
 * Input:
 * - First line: integer n representing the number of vertices
 * - Next n lines: n space-separated integers representing the adjacency matrix
 *   (use -1 to indicate no direct edge between two vertices)
 *
 * Output:
 * - Print the shortest distance matrix where the value at row i and column j
 *   represents the shortest distance from vertex i to vertex j
 *
 * Example:
 * Input:
 * 4
 * 0 5 -1 10
 * -1 0 3 -1
 * -1 -1 0 1
 * -1 -1 -1 0
 *
 * Output:
 * 0 5 8 9
 * -1 0 3 4
 * -1 -1 0 1
 * -1 -1 -1 0
 *
 * Explanation:
 * The Floyd-Warshall algorithm works by considering each vertex as an
 * intermediate point and updating the shortest paths between all pairs of
 * vertices. For example, the shortest path from vertex 1 to vertex 3 is
 * improved via vertex 2 with total cost 8.
 */

#include <stdio.h>

#define INF 1000000000

int main() {
    int n;
    scanf("%d", &n);

    int dist[105][105];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
            if(dist[i][j] == -1 && i != j)
                dist[i][j] = INF;
        }
    }

    /* Floyd-Warshall */
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF &&
                   dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    /* Print result: -1 for unreachable */
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(j > 0) printf(" ");
            if(dist[i][j] == INF)
                printf("-1");
            else
                printf("%d", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
