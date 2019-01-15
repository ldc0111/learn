/*************************************************************************
	> File Name: 041.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月12日 星期六 17时39分58秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <cstdio>
#include <string.h>
using namespace std;

#define maxn 1000
#define maxk 10
int  dp[2][maxk + 5][maxk + 5][1000] = {0};

void add(int *a, int *b){
    a[0] = a[0] > b[0] ? a[0] : b[0];
    for (int i = 1; i <= a[0]; i++) {
        a[i] += b[i];
    }
    for (int i = 1; i <= a[0]; i++) {
        if(a[i] < 10) continue;
        a[i + 1] += a[i] / 10;
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
int main() {
    int wallsize,m;
    int i,j,k,l;
    cin >> wallsize >> m;
    if(wallsize  == 1) {
        cout << m << endl;
        return 0;
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            if (i == j) continue;
            dp[0][i][j][0] = dp[0][i][j][1] = 1;
        }
    }
    for (i = 3; i <= wallsize; i++) {
        for (j = 0; j < m; j++) {
            for (k = 0; k < m; k++) {
                memset(dp[i % 2][k][j], 0, sizeof(dp[i % 2][k][j]));
                //dp[i % 2][k][j][0] = 0;
                for (l = 0; l < m; l++) {
                    if(l == j) continue;//和上一个不能相同//这一个的颜色等于上一个非这个颜色的和
                    add(dp[i % 2][k][j], dp[(i % 2) ^ 1][k][l]);
                    //dp[i % 2][k][j] += dp[(i % 2) ^ 1][k][l];
                }
            }
        }
    }
    int ans[maxn] = {0};
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            if (i == j) continue;
            add(ans,dp[wallsize % 2][i][j]);
        }
    }
    print(ans);
    return 0;
}
