/*************************************************************************
	> File Name: 047.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月12日 星期六 22时51分18秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
using namespace std;

#define maxn 10000
int dp[maxn + 5];
void print(int n){
    for (int i = 0; i <= n; i++) {
        printf("%d ", dp[i]);
    }
    printf("\n");
}
int main() {
    int v,n,a,b;
    scanf("%d%d", &v, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        for (int j = v; j >= a; j--) {
            dp[j] = max(dp[j],dp[j - a] + b);
        }
        print(v);
    }
    printf("%d\n", dp[v]);
    return 0;
}
