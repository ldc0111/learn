#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct unionset{
    int *data, *size;
    int n,cnt;
}unionset;

unionset *init(int n) {
    unionset *p = (unionset *)malloc(sizeof(unionset));
    p->size = (int *)malloc(sizeof(int) * n);
    p->data = (int *)malloc(sizeof(int) * n);
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
}
int find(unionset *u, int n) {
    if (u->data[n] == n) return n;
    int father = find(u, u->data[n]);
    u->data[n] = father;
    return father;
}
int merge(unionset *u, int a, int b) {
    int fathera = find(u, a), fatherb = find(u, b);
    //printf("%d %d\n", fathera, fatherb);
    if (fathera == fatherb) return 1;
    if (u->size[a] < u->size[b]) {
        u->data[fathera] = fatherb;
        u->size[fatherb] += u->size[fathera];
    } else {
        u->data[fatherb] = fathera;
        u->size[fathera] += u->size[fatherb];
    }
    u->cnt -= 1;
    return 0;
}


int main(){
    int n, m, a, b,cnt = 0;
    scanf("%d%d", &n, &m);
    unionset *u = init(m);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        cnt += merge(u, a, b);
    }
    printf("%d\n", cnt);
    return 0;
}