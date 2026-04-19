/*
 * Day 78 - Minimum Spanning Tree using Prim's Algorithm
 *
 * Problem: Given weighted undirected graph, compute total weight of Minimum
 *          Spanning Tree using Prim's algorithm.
 *
 * Input Format:
 * n m
 * u v w
 * ...
 *
 * Output Format:
 * Total weight of MST.
 *
 * Sample Input:
 * 4 5
 * 1 2 3
 * 1 3 5
 * 2 3 1
 * 2 4 4
 * 3 4 2
 *
 * Sample Output:
 * 6
 *
 * Explanation:
 * One possible MST edges: (2-3), (3-4), (1-2)
 */

#include <stdio.h>

#define INF 1000000000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int graph[105][105];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            graph[i][j] = INF;

    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int selected[105] = {0};
    selected[1] = 1;
    int edges = 0, total = 0;

    while(edges < n - 1) {
        int min = INF, x = 0, y = 0;

        for(int i = 1; i <= n; i++) {
            if(selected[i]) {
                for(int j = 1; j <= n; j++) {
                    if(!selected[j] && graph[i][j] < min) {
                        min = graph[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        if(x == 0) break;
        selected[y] = 1;
        total += graph[x][y];
        edges++;
    }

    printf("%d\n", total);
    return 0;
}
