/*************************************************************************
	> File Name: 6.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月27日 星期四 20时03分00秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
using namespace std;
//大前提同一个作用域
//函数名相同
//函数重载只跟函数名个参数列表有关，
//本质他是不同的函数
//重载函数不能通过函数名输出地址
int add(int) {
    return 1;
}

int add(double) {
    return 1;
}
int add(bool) {
    return 1;
}

int add(float) {
    return 1;
}
int main() {
    typedef int (*a)(int);
    typedef int (*b)(double);
    typedef int (*c)(bool);
    a p1 = add;
    b p2 = add;
    c p3 = add;

    printf("%p\n%p\n%p\n", p1, p2, p3);
    
    return 0;
}

