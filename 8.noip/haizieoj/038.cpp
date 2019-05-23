/*************************************************************************
	> File Name: 038.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月11日 星期五 17时12分41秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
using namespace std;
#define maxn 100
int a[2][maxn] = {0};

//1 2 3 5

int main() {
    int n;
    cin >> n;
    a[0][0] = a[1][0] = 1;
    a[0][1] = 1;
    a[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= a[(i - 1) % 2][0]; j++) {
            a[i % 2][j] = a[(i - 1) % 2][j] + a[(i - 2) % 2][j];
        }
        a[i % 2][0] = a[(i - 1) % 2][0];
        for (int k = 1; k <= a[i % 2][0]; k++) {
            if (a[i % 2][k] < 10) continue;
            a[i % 2][k + 1] += a[i % 2][k]/ 10;
            a[i % 2][k] = a[i % 2][k] % 10;
            if(k == a[i % 2][0]) a[i % 2][0]++;
        }
    }
    for (int i = a[n % 2][0]; i >= 1; i--) {
        printf("%d", a[n % 2][i]);
    }
    printf("\n");
    return 0;
}
