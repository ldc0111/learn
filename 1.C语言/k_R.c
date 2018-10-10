/*************************************************************************
	> File Name: k_R.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月20日 星期四 18时34分45秒
 ************************************************************************/

#include<stdio.h>

int is_prime(x)
int x;
{
    for(int i = 2; i * i <= x; i++){
        if(x % i == 0) return 0;
    }
    return 1;
}


int main(){
    printf("%d", is_prime(2));
    return 0;
}
