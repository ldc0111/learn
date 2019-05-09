#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500

typedef struct Graph {
    int mat[MAX_N][MAX_N];
    int n;
}Graph;

void init(Graph *g, int len) {
    g->n = len;
    memset(g->mat, 0, sizeof(g->mat));
}

void insert(Graph *g, int a, int x, int y) {
    if(x < 0 || x > g->n || y < 0 || y >= g->n){
        return ;
    }
    g->mat[x][y] = 1;
    if(a == 1) g->mat[y][x] = 1;
    return ;
}

void output(Graph *g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d", g->mat[i][j]);
            j != g->n - 1 && printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int n,m;
    int a,x,y;
    Graph * g = (Graph *)malloc(sizeof(Graph));
    scanf("%d%d", &n, &m);
    init(g, n);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &x, &y);
        insert(g,a,x,y);
    }
    output(g);
    return 0;
}