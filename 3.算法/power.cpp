/*************************************************************************
	> File Name: power.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月05日 星期一 11时50分35秒
 ************************************************************************/

#include<iostream>
using namespace std;

int poww(int a,int b){
    int ans = 1;
    while(b){
        if(b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}



int main(){
    int a,b;
    while(scanf("%d%d", &a,&b) != EOF) {
        printf("%d\n",poww(a,b));
    }

    return 0;
}
