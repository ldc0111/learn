/*************************************************************************
	> File Name: 3.unionset.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月20日 星期日 17时05分54秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct unionset{
    int *fa;
    int *size;
    int n;
}unionset;

unionset *init(int n) {
    unionset *u = (unionset *)calloc(sizeof(unionset), 1);
    u->fa = (int *)malloc(sizeof(int) *n);
    for (int i = 0; i < n; i++) {
        u->fa[i] = i;
    }
    u->n = n;
    return u;
}
int find(unionset *u, int x) {
    if (u->fa[x] != x) return find(u, u->fa[x]);
    return x;
}

int merge(unionset *u, int a, int b) {
    int fa = find(u,a), fb = find(u,b);
    if (fa == fb) return 0;
    u->fa[fa] = fb;
    return 1;
}

void output(unionset *u) {
    for (int i = 0; i < u->n; i++) {
        printf("(%d, %d)\t", i, u->fa);
        if (i + 1 < u->n && i + 1 % 5 == 0) printf("\n");
    }
    printf("\n\n");
    return ;
}




void clear(unionset *u) {
    if (u == NULL) return ;
    free(u->fa);
    free(u);
    return ;
}

int main() {
    srand(time(0));
    int op, a, b;
    #define MAX_OP 10
    #define MAX_N 10
    unionset *u = init(MAX_N);
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        a = rand() % MAX_N;
        b = rand() % MAX_N;
        switch(op) {
            case 0: {
                printf("find %d <-> %d = %d", a, b,find(u,b));
            }break;
            default: {
                printf("union %d <-> %d = %d",a,b,merge(u, a,b));
            }break;
        }
        output(u);
    }

    return 0;
}












