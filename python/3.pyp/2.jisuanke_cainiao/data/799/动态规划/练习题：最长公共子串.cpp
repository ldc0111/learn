#include <stdio.h>
#include <stdlib.h>
int lengthOfLCS(char *str1, char *str2) {
	int ans = 0;
    #define maxn 1000
    int dp[maxn + 5][maxn + 5] = {0};
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] != str2[j - 1]) continue;
            dp[i][j] = dp[i - 1][j - 1] + 1;
            if (dp[i][j] > ans) ans = dp[i][j];
        }
    }
    return ans;
}
int main() {
	char a[1000+10];
	char b[1000+10];
	scanf("%s %s", a, b);
	printf("%d\n", lengthOfLCS(a, b));
}