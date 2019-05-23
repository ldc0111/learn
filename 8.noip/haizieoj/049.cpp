/*************************************************************************
	> File Name: 049.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月13日 星期日 09时19分57秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
using namespace std;
#define maxn 10000
int dp[maxn + 5] = {0};

int main() {
    int v,n,a,b,c;
    scanf("%d%d", &v, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &a, &b,&c);
        for (int j = 0; j < c; j++) {
            if((j+1) * a > v) break;
            for (int k = v; k >= a; k--) {
                dp[k] = max(dp[k], dp[k - a] + b);
            }
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}

