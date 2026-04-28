// Day 87: Advanced Algorithms - Heavy Light Decomposition
// Problem: Implement Heavy Light Decomposition for tree path queries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

struct Edge {
    int to, next;
} edge[MAXN * 2];

int head[MAXN], cnt = 0;
int size[MAXN], depth[MAXN], parent[MAXN];
int heavy[MAXN], top[MAXN], pos[MAXN], dfs_pos = 0;
int tree[MAXN * 4], lazy[MAXN * 4];

void addEdge(int u, int v) {
    edge[++cnt] = (struct Edge){v, head[u]};
    head[u] = cnt;
    edge[++cnt] = (struct Edge){u, head[v]};
    head[v] = cnt;
}

// First DFS to calculate size and find heavy child
void dfs1(int u, int p) {
    size[u] = 1;
    parent[u] = p;
    heavy[u] = -1;
    
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == p) continue;
        
        depth[v] = depth[u] + 1;
        dfs1(v, u);
        size[u] += size[v];
        
        if (heavy[u] == -1 || size[v] > size[heavy[u]]) {
            heavy[u] = v;
        }
    }
}

// Second DFS to decompose the tree
void dfs2(int u, int t) {
    top[u] = t;
    pos[u] = ++dfs_pos;
    
    if (heavy[u] != -1) {
        dfs2(heavy[u], t);
    }
    
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == parent[u] || v == heavy[u]) continue;
        dfs2(v, v);
    }
}

// Segment tree operations
void pushDown(int node, int l, int r) {
    if (lazy[node]) {
        tree[node * 2] += lazy[node];
        tree[node * 2 + 1] += lazy[node];
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tree[node] += val;
        lazy[node] += val;
        return;
    }
    
    pushDown(node, l, r);
    int mid = (l + r) / 2;
    
    if (ql <= mid) update(node * 2, l, mid, ql, qr, val);
    if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, val);
}

int query(int node, int l, int r, int pos) {
    if (l == r) return tree[node];
    
    pushDown(node, l, r);
    int mid = (l + r) / 2;
    
    if (pos <= mid) return query(node * 2, l, mid, pos);
    else return query(node * 2 + 1, mid + 1, r, pos);
}

// Heavy Light Decomposition path update
void pathUpdate(int u, int v, int val, int n) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            int temp = u; u = v; v = temp;
        }
        update(1, 1, n, pos[top[u]], pos[u], val);
        u = parent[top[u]];
    }
    
    if (depth[u] > depth[v]) {
        int temp = u; u = v; v = temp;
    }
    update(1, 1, n, pos[u], pos[v], val);
}

// Heavy Light Decomposition path query
int pathQuery(int u, int n) {
    return query(1, 1, n, pos[u]);
}

int main() {
    int n, q;
    printf("Enter number of nodes and queries: ");
    scanf("%d %d", &n, &q);
    
    printf("Enter %d edges:\n", n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    
    // Build Heavy Light Decomposition
    depth[1] = 0;
    dfs1(1, 0);
    dfs2(1, 1);
    
    printf("\nProcessing queries:\n");
    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);
        
        if (type == 1) {
            // Path update
            int u, v, val;
            scanf("%d %d %d", &u, &v, &val);
            pathUpdate(u, v, val, n);
            printf("Updated path from %d to %d with value %d\n", u, v, val);
        } else {
            // Point query
            int u;
            scanf("%d", &u);
            printf("Value at node %d: %d\n", u, pathQuery(u, n));
        }
    }
    
    return 0;
}