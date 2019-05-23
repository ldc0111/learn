/*************************************************************************
	> File Name: 1.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月27日 星期四 19时17分08秒
 ************************************************************************/

#include<stdio.h>
//c语言函数调用的的时候不能有初始值
int add(int a = 0, int b = 0) {
    return a + b;
}

int main() {
    int a = 6, b = 6;
    printf("%d\n", add(a, b));
    return 0;
}
