/*************************************************************************
	> File Name: 039.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月11日 星期五 17时32分58秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
using namespace std;
#define maxn 500
int a[4][maxn] ={0};


int main() {
    int n = 0;
    cin >> n;
    a[0][0] = a[1][0] = a[2][0] = a[3][0] = 1;
    a[0][1] = a[1][1] = 0;
    a[2][1] = a[3][1] = 1;
    for (int i = 4; i <= n; i++) {
        for (int j = 1; j <= a[(i - 1) % 4][0]; j++) {
            a[i % 4][j] = a[(i - 2) % 4][j] + a[(i - 3) % 4][j];
        }
        a[i % 4][0] = a[(i - 1) % 4][0];
        for (int k = 1; k <= a[i % 4][0]; k++) {
            if (a[i % 4][k] < 10) continue;
            a[i % 4][k + 1] += a[i % 4][k] / 10;
            a[i % 4][k] = a[i % 4][k] % 10;
            if (k == a[i % 4][0]) a[i % 4][0]++;
        }
    }
    for (int i = a[n % 4][0]; i >= 1; i--) {
        cout << a[n % 4][i];
    }
    cout << endl;
    return 0;
}

