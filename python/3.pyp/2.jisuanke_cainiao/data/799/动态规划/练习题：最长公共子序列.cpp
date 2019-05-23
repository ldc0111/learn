#include <stdio.h>
#include <stdlib.h>
int lengthOfLCS(char *str1, char *str2) {
    #define maxn 1000
    #define max(a,b) ((a) > (b) ? (a) : (b))
    int dp[maxn + 5][maxn + 5] = {0};
	int n = strlen(str1);
    int m = strlen(str2);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max(max(dp[i][j - 1],dp[i - 1][j]),dp[i - 1][j - 1] + (str1[i - 1] == str2[j - 1]));
            //printf("%d |%d| ", dp[i][j], dp[i - 1][j - 1] + (str1[i - 1] == str2[j - 1]));
        }
        //printf("\n");
    }
    return dp[n][m];
}
int main() {
	char a[1000+10];
	char b[1000+10];
	scanf("%s %s", a, b);
	printf("%d\n", lengthOfLCS(a, b));
}