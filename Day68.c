/*
 * Day 68 - Topological Sort (Kahn's BFS Algorithm)
 *
 * Problem: Implement topological sorting using in-degree array and queue (Kahn's Algorithm).
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

void topoSort(int V, struct Node* adj[]) {
    int indegree[V];
    for(int i = 0; i < V; i++)
        indegree[i] = 0;
    
    /* Calculate in-degree of each vertex */
    for(int i = 0; i < V; i++) {
        struct Node* temp = adj[i];
        while(temp != NULL) {
            indegree[temp->vertex]++;
            temp = temp->next;
        }
    }
    
    /* Queue for BFS */
    int queue[V];
    int front = 0, rear = 0;
    
    /* Enqueue all vertices with in-degree 0 */
    for(int i = 0; i < V; i++) {
        if(indegree[i] == 0)
            queue[rear++] = i;
    }
    
    int topo[V];
    int count = 0;
    
    while(front < rear) {
        int node = queue[front++];
        topo[count++] = node;
        
        struct Node* temp = adj[node];
        while(temp != NULL) {
            int it = temp->vertex;
            indegree[it]--;
            if(indegree[it] == 0)
                queue[rear++] = it;
            temp = temp->next;
        }
    }
    
    if(count != V) {
        printf("Cycle detected! Topological sort not possible.\n");
        return;
    }
    
    for(int i = 0; i < count; i++)
        printf("%d ", topo[i]);
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
