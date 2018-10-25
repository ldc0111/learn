/*************************************************************************
	> File Name: test.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月23日 星期二 19时39分04秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 1000
#define key 20 

struct Edge {
    int v,n;//ｖ目的节点　ｎ是这个链的，这个节点的上一个节点
}g[max << 1];
//head 下标是节点，以这个节点为链的最后一个出节点
int head[max + 5] = {0},cnt = 0;//ｃｎｔ边数
inline void add(int a,int b){
    g[++cnt].v = b;
    g[cnt].n = head[a];//起始节点是第几条边连着的
    head[a] = cnt;
    return;
}
//gas[i][j]->i shang zou 2 jiecifangbu daodadebianhao
int gas[max][key] = {0}, dep[max] = {0};

void dfs(int u,int father){
    gas[u][0] = father;
    dep[u] = dep[father] + 1;
    for(int i = 1; i < key; i++){
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }
    for(int i = head[u];i;i = g[i].n){
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
    for(int i = key - 1; i >= 0; i--){//二分
        if(gas[a][i] != gas[b][i]) a = gas[a][i],b = gas[b][i];
    }
    return gas[a][0];
}
int main(){
    int n,a,b;
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int a,b;
        scanf("%d%d", &a, &b);
        add(a,b);
        add(b,a);
    }
    dfs(1,0);
    while(scanf("%d%d",&a, &b) != EOF) {
        printf("lca(%d,%d) = %d, a->b = %d\n", a, b, lca(a,b), dep[a] + dep[b] - 2 * dep[lca(a,b)]);
    }
    return 0;
}
