#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct unionset{
    int *data, *size;
    int n,cnt;
}unionset;

unionset * init(int n) {
    unionset *p = (unionset *)malloc(sizeof(n));
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = (int *)malloc(sizeof(int) * n);
    p->n = n;
    p->cnt = n;
    for (int i = 0; i < n; i++) {
        p->data[i] = i;
        p->size[i] = 1;
    }
    return p;
}
void clear(unionset *u) {
    if (u == NULL) return ;
    free(u->data);
    free(u->size);
    free(u);
    return ;
}
int find(unionset *u, int n) {
    if (u->data[n] == n) return n;
    int father = find(u, u->data[n]);
    u->data[n] = father;
    return father;
}
int merge(unionset *u, int a, int b) {
    int father_a = find(u, a), father_b = find(u, b);
    //printf("%d %d %d %d\n", a, b, father_a, father_b);
    if (father_a == father_b) return 0;
    if (u->size[father_a] < u->size[father_b]) {
        u->data[father_a] = father_b;
        u->size[father_b] += u->size[father_a];
    } else {
        u->data[father_b] = father_a;
        u->size[father_a] += u->size[father_b];
    }
    u->cnt -= 1;
    //printf("%d\n", u->cnt);
    return 1;
}


int main() {
    int n,m, a,b;
    scanf("%d%d", &n, &m);
    unionset *u = init(n);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        //printf("%d ", i);
        merge(u, a, b);
    }
    printf("%d\n", u->cnt);
    return ;
}