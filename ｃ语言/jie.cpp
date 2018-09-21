/*************************************************************************
	> File Name: jie.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月20日 星期四 18时42分15秒
 ************************************************************************/

#include<iostream>
using namespace std;

int jiee(int n){

    return n == 1? 1:jiee(n - 1) * n;
}

int main(){
    int n;
    scanf("%d", &n);
    printf("%d",jiee(n));
    return 0;
}
