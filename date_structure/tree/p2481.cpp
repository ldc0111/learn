/*************************************************************************
	> File Name: p2481.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月25日 星期四 16时50分17秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 500000
#define key 20

struct {
    int n,v;
}g[max << 1];

int head[max + 5],cnt = 0;
inline void  add(int a,int b){
    g[++cnt].v = b;
    g[cnt].n = head[a];
    head[a] = cnt;
}
int gas[max][key] = {0}, dep[max] = {0};

void dfs(int u,int father){
    gas[u][0] = father;
    dep[u] = dep[father] + 1;
    for(int i = 1; i < key; i++) {
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }
    for(int i = head[u]; i; i = g[i].n){
        if(g[i].v == father) continue;
        dfs(g[i].v,u);
    }
    return ;
}
int lca(int a,int b){
    if(dep[b] < dep[a]){
        a ^= b;
        b ^= a;
        a ^= b;
    }
    int l = dep[b] - dep[a];
    for(int i = 0; i < key; i++){
        if(l & (1 << i)) b = gas[b][i];
    }
    if(a == b) return a;
    for(int i = key -1; i >= 0; i--) {
        if(gas[a][i] != gas[b][i]) a = gas[a][i], b = gas[b][i];
    }
    return gas[a][0];
}

int main(){
    int n,m;
    int a,b,c;
    scanf("%d %d",&n,&m);
    for(int i = 1; i < n; i++){
        scanf("%d%d", &a,&b);
        add(a,b);
        add(b,a);
    }
    dfs(1,0);
    //while(scanf("%d%d", &a,&b) != EOF){
    //    printf("lca(%d,%d) = %d, a->b = %d\n",a,b,lca(a,b),dep[a] + dep[b] - 2 * dep[lca(a,b)]);
    //}
    for(int i = 0; i  < m; i++){
        scanf("%d%d%d",&a,&b,&c);
        int temp1 = 
    }
    return 0;
}
