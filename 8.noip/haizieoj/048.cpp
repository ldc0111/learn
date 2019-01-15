/*************************************************************************
	> File Name: 048.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月12日 星期六 23时05分45秒
 ************************************************************************/


#include<iostream>
#include <cstdio>
using namespace std;

#define maxn 10000
int dp[maxn + 5];
int main() {
    int v,n,a,b;
    scanf("%d%d", &n, &v);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        for (int j = a; j <= v; j++) {
            dp[j] = max(dp[j],dp[j - a] + b);
        }
    }
    printf("%d\n", dp[v]);
    return 0;
}

