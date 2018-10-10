/*************************************************************************
	> File Name: bei.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月18日 星期二 20时53分00秒
 ************************************************************************/

#include<iostream>
using namespace std;


int main(){
    int n,x = 0;

    scanf("%d", &n);
    x = (n == 0);
    while(n){
        x++;
        n /= 10;
    }
    printf("%d",x);


    return 0;
}
