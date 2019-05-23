#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 1000
#define INF 0x3f3f3f3f

typedef struct Graph{
    int n;
    int mat[maxn][maxn];
    int visited[maxn], dist[maxn];
}Graph;

Graph* init(int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->n = n;
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->mat[i][j] = INF;
        }
    }
    return g;
}
void insert(Graph *g, int x,int y, int weight) {
    if (weight > g->mat[y][x]) return ;
    g->mat[y][x] = weight;
}
void dijkstra(Graph *g, int v) {
    for (int i = 0; i < g->n; i++) {
        g->visited[i] = 0;
        g->dist[i] = INF;
    }
    g->dist[v] = 0;
    for (int i = 0; i < g->n; i++) {
        int min_vertex, min_dist = INF;
        for (int j = 0; j < g->n; j++) {
            if (g->visited[j] || g->dist[j] >= min_dist) continue;
                min_dist = g->dist[j];
                min_vertex = j;
        }
        g->visited[min_vertex] = 1;
        for (int j = 0; j < g->n; j++) {
            if (g->visited[j] || min_dist + g->mat[min_vertex][j] >= g->dist[j]) continue;
                g->dist[j] = min_dist + g->mat[min_vertex][j];
        }
    }
}



int main() {
    int n,m,k,min_vertex, min_dist = INF;
    int fd[maxn] = {0};
    int a,b,c;
    scanf("%d%d%d",&n, &m, &k);
    Graph *g = init(n);
    for (int i = 0; i < k; i++) {
        scanf("%d", &fd[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d",&a,&b,&c);
        insert(g,a,b,c);
    }
    dijkstra(g,0);
    for (int i = 0; i < k; i++) {
        //printf("%d %d\n",fd[i],g->dist[fd[i]]);
        if (g->dist[fd[i]] < min_dist) {
            min_vertex = fd[i];
            min_dist = g->dist[fd[i]];
        } else if (g->dist[fd[i]] == min_dist && min_vertex > fd[i]) {
            min_vertex = fd[i];
        }
    }
    printf("%d\n",min_vertex);
    return 0;
}