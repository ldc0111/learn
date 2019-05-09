#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 105
#define INF 0x3f3f3f3f
typedef struct Graph{
    int n;
    int mat[maxn][maxn];
    int vis[maxn],dist[maxn];
}Graph;

Graph *init(int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->n = n;
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->mat[i][j] = INF;
        }
        g->vis[i] = 0;
        g->dist[i] = INF;
    }
    return g;
}

int prim(Graph *g,int v) {
    int total = 0;
    g->dist[v] = 0;
    for (int i = 0; i < g->n; i++) {
        int min_dist = INF, min_vertex;
        for (int j = 0; j < g->n; j++) {
            if (g->vis[j] || g->dist[j] >= min_dist) continue;
            min_dist = g->dist[j];
            min_vertex = j;
        }
        total += min_dist;
        g->vis[min_vertex] = 1;
        for (int j = 0; j < g->n; j++) {
            if (g->vis[j] || g->mat[min_vertex][j] >= g->dist[j]) continue;
            g->dist[j] = g->mat[min_vertex][j];
        }
    }
    return total;
}

int main() {
    int n;
    scanf("%d", &n);
    Graph *g = init(n);
    for (int i =0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &g->mat[i][j]);
            if(i == j) g->mat[i][j] = INF;
        }
    }
    printf("%d\n",prim(g,0));
    return 0;
}