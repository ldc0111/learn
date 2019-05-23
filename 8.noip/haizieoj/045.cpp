/*************************************************************************
	> File Name: 045.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月12日 星期六 21时31分09秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

#define maxn 1000
#define max(a,b) ((a) > (b) ? (a) : (b))
int dp[maxn + 5][maxn + 5];
char a[maxn + 5], b[maxn + 5];


int main() {
    int ans = 0,x = 0,y = 0,len1 = 0, len2 = 0;
    scanf("%s%s",a,b);
    len1 = strlen(a); len2 = strlen(b);
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            x = i + 1;
            y = j + 1;
            dp[x][y] = max((dp[x - 1][y - 1] + (a[i] == b[j])), max(dp[x - 1][y], dp[x][y - 1]));
        }
    }
    /*for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }*/
    printf("%d\n",dp[len1][len2]);
    return 0;
}
