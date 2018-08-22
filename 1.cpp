/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年08月22日 星期三 22时51分41秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define maxn 10000
int prime[maxn + 5] ={0};
void init(){
    for(int i=  2; i< maxn; i++ ) {
        if (!prime[i]){
            prime[++prime[0]] = i;
        }
        for(int j = 1; j <= prime[0]; j++){
            if(i * prime[j] >= maxn) continue;
            prime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}


int main(){
    init();
    cout << prime[6];

    return  0;
}
