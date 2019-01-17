/*************************************************************************
> File Name: duotai.h
> Author: 小学肄业
> Mail: 18734914520@163.com or weirufeng@haizeix.com
> Created Time: 二  1/15 19:04:34 2019
> Description:
************************************************************************/

#ifndef _DUOTAI_H
#define _DUOTAI_H
typedef void demo;
typedef void derived;

demo* demo_init(int i, int j);
int getI(demo *pthis);
int getJ(demo *pthis);
int demo_add(demo *pthis, int v);
void demo_free(demo *pthis);

derived* derived_init(int i, int j, int k);
int getK(derived *pthis);
int derived_add(derived *pthis, int v);
void derived_free(derived *pthis);
#endif
