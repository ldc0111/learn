/*************************************************************************
	> File Name: 042.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月12日 星期六 18时56分15秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
using namespace std;
#define max(a,b) ((a) > (b) ? (a) : (b))
#define maxn 10000
#define maxm 100
int dp[maxn + 5] = {0};
int a[maxm + 5] = {0};

int main() {
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    dp[0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = a[i]; j <= n; j++) {
            dp[j] = (dp[j] + dp[j - a[i]]) % 9973;
        }
    }
    cout << dp[n] << endl;
    return 0;
}
