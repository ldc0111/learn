#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 1000

typedef struct Graph {
    int n;
    int color[MAX_N];
    int mat[MAX_N][MAX_N];
}Graph;

void init_Graph(Graph *g, int input_n) {
    g->n = input_n;
    for (int i = 0; i < g->n; i++) {
        g->color[i] = 0;
        for (int j = 0; j < g->n; j++) {
            g->mat[i][j] = 0;
        }
    }
}

void insert(Graph *g, int x, int y) {
    g->mat[x][y] = 1;
    g->mat[y][x] = 1;
}

void floodfill(Graph *g) {
    int color_cnt = 0;
    int q[MAX_N];
    for (int i = 0; i < g->n; i++) {
        if (g->color[i] != 0) continue;//染过
        int l = 0,r = 0;
        color_cnt++;
        g->color[i] = color_cnt;
        q[r++] = i;
        while (l < r) {
            int vertex = q[l++];
            for (int i = 0; i < g->n; i++) {
                if (g->mat[vertex][i] && g->color[i] == 0) {
                	g->color[i] = color_cnt;
                    q[r++] = i;
                }
            }
        }
    }
    for (int i = 1; i <= color_cnt; i++) {
        printf("%d:",i);
        for (int j = 0; j < g->n; j++) {
            if(g->color[j] != i) continue;
            printf("%d ", j);
        }
        printf("\n");
    }
}

int main() {
    int n,m,a,b;
    Graph *g = (Graph *)malloc(sizeof(Graph));
    scanf("%d%d",&n, &m);
    init_Graph(g,n);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a ,&b);
        insert(g,a,b);
    }
    floodfill(g);
    
    return 0;
}