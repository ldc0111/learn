/*************************************************************************
	> File Name: exception.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 14时14分48秒
 ************************************************************************/

#include<stdio.h>
int div(int a, int b){
    if (b != 0)return a/b;
    else return 0;
}

int main() {
    printf("%d\n", div(1.0, 1.0));
    printf("%d\n", div(1,0));
    printf("%d\n", div(0,10));
    return 0;
}
