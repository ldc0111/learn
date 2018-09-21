/*************************************************************************
	> File Name: fun.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月20日 星期四 19时53分40秒
 ************************************************************************/

#include<stdio.h>

#define P(func){\
    printf("%s = %d\n", #func, func);\
}



int is_prime(int x);
int max_int(int n, ...);


int main(){
    for(int  i = 2; i < 100; i++){
        if(is_prime(i)){
            printf("%d\n",i);
        }
    }
    P(max_int(3,1,2,7));
    return 0;
}
