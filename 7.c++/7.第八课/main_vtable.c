/*************************************************************************
> File Name: main_vtable.c
> Author: 小学肄业
> Mail: 18734914520@163.com or weirufeng@haizeix.com
> Created Time: 二  1/15 19:16:49 2019
> Description:
************************************************************************/

#include <stdio.h>
#include "duotai.h"
void how_to_select(demo *p, int v) {
    int r = demo_add(p, v);
    printf("res = %d\n", r);
}
int main() {
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    demo *pb = demo_init(1, 2);
    derived *pd = derived_init(1, 2, 3);
    printf("i = %d\n", getI(pb));
    printf("j = %d\n", getJ(pb));
    printf("add = %d\n", demo_add(pb, 5));
    printf("i = %d\n", getI(pd));
    printf("j = %d\n", getJ(pd));
    printf("k = %d\n", getK(pd));
    printf("add = %d\n", derived_add(pd, 5));
    how_to_select(pb, 1);
    how_to_select(pd, 2);
    demo_free(pb);
    derived_free(pd);
    return 0;
}

