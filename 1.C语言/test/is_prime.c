/*************************************************************************
	> File Name: is_prime.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月07日 星期日 11时25分32秒
 ************************************************************************/

#include<stdio.h>


int  is_prime(int x){
    if(x <= 1) return 0;
    for(int i = 2; i * i <= x; i++){
        if(x % i == 0) return 0;
    }
    return 1;
}
