/*************************************************************************
	> File Name: is_palindrome.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月05日 星期一 12时01分29秒
 ************************************************************************/

#include <stdio.h>


int is_palindrome(int x){
    int m = x,n = 0;
    while(m){
        n = n* 10 + m % 10;
        m /= 10;
    }
    return n == x;
}


int main(){
    int a;
    while(scanf("%d", &a) != EOF){
        printf("%d\n",is_palindrome(a));
    }

    return 0;
}
