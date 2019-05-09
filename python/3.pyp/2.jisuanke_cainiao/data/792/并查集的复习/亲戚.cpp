#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct unionset{
    int *data, *size;
    int cnt, n;
}unionset;


unionset *init(int n) {
    unionset *p = (unionset*)malloc(sizeof(unionset));
    p->size = (int *)malloc(sizeof(int) * n);
    p->data = (int *)malloc(sizeof(int) * n);
    p->n = n; p->cnt = n;
    for (int i = 0; i < n; i++) {
        p->data[i] = i;
        p->size[i] = 1;
    }
    return p;
}
int find(unionset *u, int n) {
    if (u->data[n] == n) return n;
    int father = find(u, u->data[n]);
    u->data[n] = father;
    return father;
}


int merge(unionset *u, int a, int b) {
    int fa = find(u, a), fb = find(u, b);
    if (fa == fb) return 0;
    if (u->size[fa] < u->size[fb]) {
        u->data[fa] = fb;
        u->size[fb] += u->size[fa];
    } else {
        u->data[fb] = fa;
        u->size[fa] += u->size[fb];
    }
    u->cnt -= 1;
    return 1;
}


int main(){
    int n, m, p, a, b;
    scanf("%d%d%d", &n, &m, &p);
    unionset *u = init(n);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        merge(u, a, b);
    }
    for (int i = 0; i < p; i++) {
        scanf("%d%d", &a, &b);
        if (find(u, a) == find(u, b)) {
            printf("Yes\n");
        }else {
            printf("No\n");
        }
    }
    return 0;
}