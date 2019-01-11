/*************************************************************************
	> File Name: 6.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 20时27分48秒
 ************************************************************************/

#include<iostream>
#include <stdlib.h>
#include "./6.h"
using namespace std;
typedef struct class_demp{
    int a;
    int b;
}class_demp;
demo * demo_init(int i, int j) {
    class_demp *p = (class_demp *)malloc(sizeof(class_demp));
    if (p != NULL) {
        p->a = i;
        p->b = j;
    }
    return p;
}
int getI(demo * pthis) {
    class_demp *p = (class_demp *)pthis;
    return p->a;
}
int getJ(demo * pthis){
    class_demp *p = (class_demp * )pthis;
    return p->b;
}
int add(demo *pthis, int value) {
    class_demp *p = (class_demp *)pthis;
    return p->a + p->b + value;
}

void free_demo(demo *pthis){
    free(pthis);
}
