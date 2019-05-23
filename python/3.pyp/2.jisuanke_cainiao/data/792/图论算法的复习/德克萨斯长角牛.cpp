#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 2505
#define INF 0x3f3f3f3f
typedef struct graph{
    int n;
    int mat[maxn][maxn];
    int dist[maxn],vis[maxn];
}graph;

graph *init(int n) {
    graph *g = (graph *)malloc(sizeof(graph));
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->mat[i][j] = INF;
        }
        g->vis[i] = 0;
        g->dist[i] = INF;
    }
    return g;
}

void insert(graph *g, int a,int b,int c) {
    if(c > g->mat[a][b]) return ;
    g->mat[a][b] = c;
    g->mat[b][a] = c;
}
void dijkstra(graph *g, int v) {
    g->dist[v] = 0;
    for (int i = 0; i < g->n; i++) {
        int min_vertex,min_dist = INF;
        for (int j = 0; j < g->n; j++) {
            if (g->vis[j] || g->dist[j] >= min_dist) continue;
            min_dist = g->dist[j];
            min_vertex = j;
        }
        g->vis[min_vertex] = 1;
        for (int j = 0; j < g->n; j++) {
            if (g->vis[j] || min_dist + g->mat[min_vertex][j] >= g->dist[j]) continue;
            g->dist[j] = min_dist + g->mat[min_vertex][j];
        }
    }
}


int main() {
    int t,c,ts,tc,a,b,d;
    scanf("%d%d%d%d", &t, &c, &ts, &tc);
    graph *g = init(t);
    for (int i = 0; i < c; i++) {
        scanf("%d%d%d",&a, &b, &d);
        insert(g,a - 1,b - 1,d);
    }
    dijkstra(g,ts - 1);
    printf("%d\n",g->dist[tc - 1]);
    return 0;
}