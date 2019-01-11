/*************************************************************************
	> File Name: 6.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 20时25分52秒
 ************************************************************************/

#ifndef _6_H
#define _6_H
typedef void demo;
demo *demo_init(int i, int j);
int getI(demo *p);
int getJ(demo *pthis);
int add(demo *pthis, int value);
void free_demo(demo *pthis);
#endif
