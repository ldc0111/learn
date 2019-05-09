#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1005


typedef struct Graph{
    int mat[MAX_N][MAX_N];
    int n;
}Graph;

void init(Graph *g, int len){
    g->n = len;
    memset(g->mat,0,sizeof(g->mat));
}
void insert(Graph *g, int x,int y){
    if(x < 0 ||x > g->n || y < 0 || y >= g->n) {
        return ;
    }
    g->mat[x][y] = 1;
}
void output(Graph *g){
    for(int i = 0; i < g->n; i++) {
        int ans = 0;
        for(int j = 0; j < g->n; j++) ans -= g->mat[i][j],ans += g->mat[j][i];
        printf("%d\n", ans);
    }
}

int main(){
    int n,m, a,b;
    scanf("%d%d", &n, &m);
    Graph *g = (Graph *)malloc(sizeof(Graph));
    init(g,n);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        insert(g,a,b);
    }
    output(g);
    return 0;
}
