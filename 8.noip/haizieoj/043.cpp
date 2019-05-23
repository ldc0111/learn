/*************************************************************************
	> File Name: 043.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月12日 星期六 20时10分59秒
 ************************************************************************/

#include <stdio.h>
#define maxn 1000
#define max(a,b) ((a > b) ? (a) :(b))
int arr[maxn + 5][maxn + 5];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            arr[i][j] += max(arr[i + 1][j], arr[i + 1][j + 1]);
        }
    }
    printf("%d\n", arr[1][1]);
    return 0;
}



