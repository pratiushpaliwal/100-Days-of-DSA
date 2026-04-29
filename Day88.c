// Day 88: Advanced Algorithms - Centroid Decomposition
// Problem: Implement Centroid Decomposition for tree distance queries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005

struct Edge {
    int to, weight, next;
} edge[MAXN * 2];

int head[MAXN], cnt = 0;
int subtree_size[MAXN];
int removed[MAXN];
int centroid_parent[MAXN];
int dist_to_centroid[MAXN];
int min_dist[MAXN];

void addEdge(int u, int v, int w) {
    edge[++cnt] = (struct Edge){v, w, head[u]};
    head[u] = cnt;
    edge[++cnt] = (struct Edge){u, w, head[v]};
    head[v] = cnt;
}

// Calculate subtree sizes
int dfs_size(int u, int parent) {
    subtree_size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == parent || removed[v]) continue;
        subtree_size[u] += dfs_size(v, u);
    }
    return subtree_size[u];
}

// Find centroid of the tree
int find_centroid(int u, int parent, int tree_size) {
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == parent || removed[v]) continue;
        if (subtree_size[v] > tree_size / 2) {
            return find_centroid(v, u, tree_size);
        }
    }
    return u;
}

// Calculate distances from centroid to all nodes in subtree
void dfs_distance(int u, int parent, int centroid, int dist) {
    dist_to_centroid[u] = dist;
    if (min_dist[u] > dist) {
        min_dist[u] = dist;
    }
    
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == parent || removed[v]) continue;
        dfs_distance(v, u, centroid, dist + edge[i].weight);
    }
}

// Centroid decomposition
void decompose(int u, int parent) {
    int tree_size = dfs_size(u, -1);
    int centroid = find_centroid(u, -1, tree_size);
    
    removed[centroid] = 1;
    centroid_parent[centroid] = parent;
    
    // Calculate distances from centroid to all nodes
    dfs_distance(centroid, -1, centroid, 0);
    
    // Recursively decompose subtrees
    for (int i = head[centroid]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (removed[v]) continue;
        decompose(v, centroid);
    }
}

// Update distance for a node
void update(int u, int new_dist) {
    int curr = u;
    while (curr != -1) {
        if (min_dist[curr] > new_dist + dist_to_centroid[u]) {
            min_dist[curr] = new_dist + dist_to_centroid[u];
        }
        curr = centroid_parent[curr];
    }
}

// Query minimum distance to any updated node
int query(int u) {
    int result = INT_MAX;
    int curr = u;
    
    while (curr != -1) {
        if (result > min_dist[curr] + dist_to_centroid[u]) {
            result = min_dist[curr] + dist_to_centroid[u];
        }
        curr = centroid_parent[curr];
    }
    
    return result == INT_MAX ? -1 : result;
}

int main() {
    int n, q;
    printf("Enter number of nodes and queries: ");
    scanf("%d %d", &n, &q);
    
    // Initialize
    for (int i = 1; i <= n; i++) {
        min_dist[i] = INT_MAX;
        centroid_parent[i] = -1;
    }
    
    printf("Enter %d edges (u v weight):\n", n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }
    
    // Build centroid decomposition
    decompose(1, -1);
    
    printf("\nProcessing queries:\n");
    printf("Query types:\n");
    printf("1 u d - Update node u with distance d\n");
    printf("2 u - Query minimum distance from node u\n");
    
    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);
        
        if (type == 1) {
            int u, d;
            scanf("%d %d", &u, &d);
            update(u, d);
            printf("Updated node %d with distance %d\n", u, d);
        } else {
            int u;
            scanf("%d", &u);
            int result = query(u);
            if (result == -1) {
                printf("No path found from node %d\n", u);
            } else {
                printf("Minimum distance from node %d: %d\n", u, result);
            }
        }
    }
    
    return 0;
}