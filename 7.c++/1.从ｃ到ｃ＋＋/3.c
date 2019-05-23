/*************************************************************************
	> File Name: 3.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月25日 星期二 19时45分54秒
 ************************************************************************/

#include<stdio.h>

f() {
    return 5;
}
g(void) {
    printf("hello\n");
}

int main() {
    printf("%d\n", f());
    g();
    return 0;
}
