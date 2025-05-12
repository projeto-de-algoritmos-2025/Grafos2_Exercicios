#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define INF 1000000000

typedef struct {
    int v, w;
} Edge;

typedef struct Node {
    int u, dist;
} Node;

typedef struct {
    Node heap[MAXN * 100];
    int size;
} MinHeap;

Edge* graph[MAXN][MAXN]; // Lista de adjacência
int weights[MAXN][MAXN]; // Matriz de pesos
int dist[MAXN];          // Distâncias mínimas
int visited[MAXN];       // Marcador de visitados

// Comparador para o heap mínimo
void push(MinHeap* h, int u, int dist) {
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->heap[p].dist <= dist) break;
        h->heap[i] = h->heap[p];
        i = p;
    }
    h->heap[i].u = u;
    h->heap[i].dist = dist;
}

Node pop(MinHeap* h) {
    Node min = h->heap[0];
    Node last = h->heap[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int a = 2 * i + 1;
        int b = 2 * i + 2;
        int minIdx = (b < h->size && h->heap[b].dist < h->heap[a].dist) ? b : a;
        if (last.dist <= h->heap[minIdx].dist) break;
        h->heap[i] = h->heap[minIdx];
        i = minIdx;
    }
    h->heap[i] = last;
    return min;
}

void dijkstra(int N, int S, int adj[][MAXN], int weights[][MAXN]) {
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    MinHeap heap = {.size = 0};
    dist[S] = 0;
    push(&heap, S, 0);

    while (heap.size > 0) {
        Node node = pop(&heap);
        int u = node.u;

        if (visited[u]) continue;
        visited[u] = 1;

        for (int v = 1; v <= N; v++) {
            if (adj[u][v] && !visited[v]) {
                int w = weights[u][v];
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    push(&heap, v, dist[v]);
                }
            }
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int adj[MAXN][MAXN] = {0};

    for (int i = 0; i < M; i++) {
        int u, v, p;
        scanf("%d %d %d", &u, &v, &p);
        adj[u][v] = adj[v][u] = 1;
        weights[u][v] = weights[v][u] = p;
    }

    int S;
    scanf("%d", &S);

    dijkstra(N, S, adj, weights);

    int minPing = INF, maxPing = -1;

    for (int i = 1; i <= N; i++) {
        if (i == S) continue;
        if (dist[i] < minPing) minPing = dist[i];
        if (dist[i] > maxPing) maxPing = dist[i];
    }

    printf("%d\n", maxPing - minPing);

    return 0;
}
