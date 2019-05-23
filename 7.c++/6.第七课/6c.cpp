/*************************************************************************
	> File Name: 6c.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 20时35分08秒
 ************************************************************************/

#include<iostream>
#include "./6.h"
#include "./6.cpp"
using namespace std;

int main() {
    demo *p = demo_init(1,2);
    printf("a = %d\n", getI(p));
    printf("b = %d\n", getJ(p));
    printf("add = %d\n", add(p, 5));
    return 0;
}

