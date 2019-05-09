#include <stdio.h>
#include <stdlib.h>

typedef struct DisjointSet {
    int *data, *he;
}DisjointSet;

void init(DisjointSet *s, int n) {
    s->data = (int *)malloc(sizeof(int) * n);
    s->he = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        s->data[i] = i;
        s->he[i] = 1;
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int find_set(DisjointSet *s, int node) {
    //printf("%d %d\n", node, s->data[node]);
    if (s->data[node] != node) {
        s->data[node] = find_set(s, s->data[node]);
    }
    return s->data[node];
}

int merge(DisjointSet *s, int a, int b) {
    int fa = find_set(s, a), fb = find_set(s, b);
    
    if (fa != fb) {
        if (s->he[fa] > s->he[fb]) swap(&fa, &fb);
        s->data[fa] = s->data[fb];
        s->he[fb] = max(s->he[fb], s->he[fa] + 1);
        return 1;
    }
    return 0;
}

void clear(DisjointSet *s) {
    free(s->data);
    free(s->he);
    free(s);
    return ;
}

int main() {
    int m, n, a, b;
    scanf("%d%d", &m, &n);
    
    DisjointSet *s = (DisjointSet *)malloc(sizeof(DisjointSet));
    init(s, m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        merge(s, a, b);
    }
    for (int i = 0; i < m; i++) {
        printf("%d\n", s->data[i]);
    }
    clear(s);
    return 0;
}