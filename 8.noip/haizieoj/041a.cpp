/*************************************************************************
	> File Name: 041a.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月14日 星期一 10时24分44秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <string.h>
#include <cmath>
using namespace std;

int dp[3][1000];
void add(int *a, int *b, int *c, int x, int y) {
    a[0] = b[0] > c[0] ? b[0] : c[0];
    for (int i = 1; i <= a[0]; i++) {
        a[i] = x * b[i] + y * c[i];
    }
    for (int i = 1; i <= a[0]; i++) {
        if (a[i] < 10) continue;
        a[i + 1] += a[i]/10;
        a[i] %= 10;
        if (i == a[0]) a[0]++;
    }
    return ;
}

void print(int *a) {
    for (int i = a[0]; i >= 1; i--) {
        cout << a[i];
    }
    cout << endl;
}

int main(){
    int w,n,temp;
    cin >> w >> n;
    if (w == 1) {
        cout << n << endl;
        return 0;
    }
    dp[0][1] = dp[0][0] = 0;
    dp[1][1] = dp[1][0] = 0;
    dp[2][1] = (n * n - n);
    //dp[2][1] = 1;
    dp[2][0] = floor(log10(n * n - n)) + 1;

    for (int i = 3; i <= w; i++) {
        memset(dp[i % 3],0,sizeof(dp[i % 3]));
        add(dp[i % 3], dp[(i - 1) % 3],dp[(i - 2) % 3], n - 2, n - 1);
        //dp[i % 3] = (n - 2) * dp[(i - 1) % 3] + (n - 1) * dp[(i - 2) % 3];
        //cout << dp[i% 3] << endl;
    }
    print(dp[w % 3]);
    //cout << dp[w % 3] * (n * n - n) << endl;
    return 0;
}
