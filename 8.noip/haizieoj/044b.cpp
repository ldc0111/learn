/*************************************************************************
	> File Name: 044b.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月12日 星期六 21时22分16秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
using namespace std;
#define maxn 500000


int dp[maxn + 5];
int a[maxn + 5];
int len[maxn + 5];
int binarysearch


int main() {
    int n,ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i <= n; i++) dp[i] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if(a[j] < a[i])
            dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}

