/*************************************************************************
	> File Name: mianji.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月30日 星期日 17时34分04秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define maxn 1000

int g[maxn][maxn] = {0};
int f[maxn][maxn] = {0};
int dp[maxn][maxn] = {0};

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 1; i <= m; j++) {
            if (g[i][j] == 0) continue;
            f[i][j] = f[i + 1][j] + 1;
        }
    }
    int ans = 0;
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int temp = f[i][j];
            for (int k = j; k <= m; k++) {
                temp = min(temp, f[i][k]);
                ans += temp;
            }
        }
    }*/
    //单调栈解法on 方
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            int k = j;
            while (f[i][k] >= j && k <= m) ++k;
            dp[i][j] = (k - j) * f[i][j] + dp[i][k];
            ans += dp[i][j];
        }
    }
    cout << ans << endl;

    return 0;
}
