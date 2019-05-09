#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxn 1000
int grape[2 * maxn][2 * maxn] = {0};
int node[2 * maxn] = {0};

typedef struct bf{
    int node;
    int lev;
}bf;
bf arr[5 * maxn] = {0};
void insert(int grape[][2 * maxn], int x, int y){
    grape[x][y] = 1;
    grape[y][x] = 1;
}
void bfs(int nod, int n, int num){
    int head = 0,tail = -1;
    arr[++tail] = (bf){nod,n};
    while (head <= tail) {
        int lev = arr[head].lev;
        int no = arr[head++].node;
        for (int i = 1; i <= num; i++) {
            if (grape[no][i] == 1 && node[i] == -1) {
                node[i] = lev + 1;
                arr[++tail] = (bf){i,lev + 1};
            }
        }
    }
}
void output(int n){
    for (int i = 1; i <= n; i++) {
        printf("%d\n",node[i]);
    }
}

int main(){
    int n, m, c;
    scanf("%d%d%d", &n, &m, &c);
    for(int i = 0; i < m; i++){
        int x,y;
        scanf("%d%d", &x, &y);
        insert(grape, x, y);
    }
    memset(node, -1, sizeof(node));
    node[c] = 0;
    bfs(c, 0, n);
    output(n);
    return 0;
}