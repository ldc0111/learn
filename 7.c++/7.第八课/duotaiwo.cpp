/*************************************************************************
	> File Name: duotaiwo.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 11时31分00秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

////////////////////.h
typedef void demo;
typedef void derived;

demo* demo_init(int i, int j);
int geti(demo * pthis);
int getj(demo * pthis);
int demo_add(demo *pthis, int v);
void demo_free(demo *pthis);


derived *derived_init(int i, int j, int k);
int getK(derived *pthis);
int derived_add(derived *pthis, int v);
void derved_free(derived *pthis);
////////////////////
///////////////////c
static int demo_virtual_add(demo *pthis, int v);
static int derived_virtual_add(derived *pthis, int v);

typedef struct vtable {
    int (*padd)(void *, int);
}vtable;
typedef struct class_demo{
    vtable *vptr;
    int i,j;
}class_demo;

typedef struct class_derived{
    class_demo d;
    int k;
}class_derived;
//声明一个父类静态变量
static vtable g_classdemo_vtr = {
    demo_virtual_add
};

struct vtable g_classderived_vtr = {
    derived_virtual_add
};
demo* demo_init(int i, int j) {
    class_demo *ret = (class_demo *)malloc(sizeof(class_demo));
    if (ret != NULL) {
        ret->vptr = &g_classdemo_vtr;
        ret->i = i;
        ret->j = j;
    }
    return ret;
}
int geti(demo *pthis) {
    class_demo *p = (class_demo *)pthis;
    return p->i;
}

int getj(demo *pthis) {
    class_demo *p = (class_demo *)pthis;
    return p->j;
}

static int demo_virtual_add(demo *pthis, int v) {
    class_demo *p = (class_demo *)pthis;
    return (p->i + p->j + v);
}

int demo_add(demo *pthis, int v) {
    class_demo *p = (class_demo *)pthis;
    return (p->vptr->padd(pthis,v));
}

void demo_free(demo *pthis) {
    free(pthis);
    return ;
}
derived *derived_init(int i, int j, int k) {
    class_derived *ret = (class_derived *)malloc(sizeof(class_derived));
    if (ret != NULL) {
        ret->d.vptr = &g_classderived_vtr;
        ret->d.i = i;
        ret->d.j = j;
        ret->k = k;
    }
    return ret;
}
int getK(derived * pthis) {
    class_derived *p = (class_derived *)pthis;
    return p->k;
}

static int derived_virtual_add(derived *pthis, int v) {
    class_derived *p = (class_derived *)pthis;
    return (p->d.i + p->d.i + p->k + v);
}

int derived_add(derived *pthis, int v) {
    class_derived *p = (class_derived *)pthis;
    return p->d.vptr->padd(pthis,v);
}
void derved_free(derived *pthis) {
    free(pthis);
    return ;
}
////////////////////////////////////////

void how_to_seclect(demo *p, int v) {
    int r = demo_add(p, v);
    printf("ret = %d\n", r);
    return ;
}


int main(){
    demo *pb = demo_init(1,2);
    derived *pd = derived_init(1,2,3);
    printf("i = %d, j =  %d\n",geti(pb),getj(pb));
    printf("fa add = %d\n",demo_add(pb,5));
    printf("i = %d, j = %d, k = %d\n",geti(pd),getj(pd),getK(pd));
    printf("cli add %d\n",derived_add(pd,5));
    how_to_seclect(pb,1);
    how_to_seclect(pd,2);
    return 0;
}
