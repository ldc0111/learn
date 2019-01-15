/*************************************************************************
	> File Name: 050.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月14日 星期一 22时18分06秒
 ************************************************************************/

#include <iostream>
#include <limits.h>
using namespace std;
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
int dp[32][10000000] = {0};


int main() {
    int n,m,a,b,c,d;
    cin >> n >> m;
    for (int i = 0; i <= m; i++) {
        dp[0][i] = 0;
        dp[1][i] = i;
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            d = INT_MAX;
            for (int k = 1; k <= j; k++) {
                a = dp[i - 1][k - 1];
                b = dp[i][j - k];
                c = max(a,b) + 1;
                d = min(d,c);
            }
            dp[i][j] = d;
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}
