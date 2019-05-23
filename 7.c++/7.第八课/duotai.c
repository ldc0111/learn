/*************************************************************************
> File Name: duotai.c
> Author: 小学肄业
> Mail: 18734914520@163.com or weirufeng@haizeix.com
> Created Time: 二  1/15 19:09:36 2019
> Description:
************************************************************************/

#include "duotai.h"
#include <stdlib.h>
static int demo_virtual_add(demo *pthis, int v);
static int derived_virtual_add(derived *pthis, int v);
typedef struct vtable { // 2、结构体中存的是虚函数地址
    int (*padd)(void*, int);
} vtable;

typedef struct class_demo {
    vtable *vptr; // 确定虚函数指针类型--》虚函数表是一个结构体，所以是结构体类型
    int i;
    int j;
} class_demo;

typedef struct class_derived {
    class_demo d;
    int k;
} class_derived;

static vtable  g_classdemo_vtr = {
    demo_virtual_add
};

static vtable g_classderived_vtr = {
    derived_virtual_add
};

demo* demo_init(int i, int j) {
    class_demo *ret = (class_demo *) malloc(sizeof(class_demo));
    if(ret != NULL) {
        ret->vptr = &g_classdemo_vtr; // 3、关联对象和虚函数表
        ret->i = i;
        ret->j = j;
    }
    return ret;
}

int getI(demo *pthis) {
    class_demo *p = (class_demo *)pthis;
    return p->i;
}

int getJ(demo *pthis) {
    class_demo *p = (class_demo*)pthis;
    return p->j;
}
// 5、定义虚函数表中指针指向的具体函数
static int demo_virtual_add(demo *pthis, int v) {
    class_demo *p = (class_demo *)pthis;
    return (p->i + p->j + v);
}

//4、分析具体的虚函数是干什么的
int demo_add(demo *pthis, int v) {
    class_demo *p = (class_demo *)pthis;
    return (p->vptr->padd(pthis, v));
}

void demo_free(demo *pthis) {
    free(pthis);
    return ;
}

derived* derived_init(int i, int j , int k) {
    class_derived *ret = (class_derived*) malloc(sizeof(class_derived));
    if(ret != NULL) {
        ret->d.vptr = &g_classderived_vtr;
        ret->d.i = i;
        ret->d.j = j;
        ret->k = k;
    }
    return ret;
}

int getK(derived *pthis) {
    class_derived *p = (class_derived *) pthis;
    return p->k;
}

static int derived_virtual_add (derived *pthis, int v) {
    class_derived *p = (class_derived *) pthis;
    return (p->d.i + p->d.j + p->k + v);
}

int derived_add(derived *pthis, int v) {
    class_derived *p = (class_derived*) pthis;
    return p->d.vptr->padd(pthis, v);
}

void derived_free(derived *pthis) {
    free(pthis);
    return ;
}

