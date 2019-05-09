#include <stdio.h>
#include <stdlib.h>
int lengthOfLNIS(int *nums, int length) {
    #define max(a,b) ((a) > (b) ? (a) : (b))
    int dp[1005] = {0};    
    int ans = 0;
    for (int i = 0; i < length; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) continue;
            dp[i] = max(dp[i],dp[j] + 1);
        }
        if (dp[i] > ans) ans = dp[i];
    }
    return ans;
}
int main() {
	int n;
	scanf("%d", &n);
	int *a = malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	printf("%d\n", lengthOfLNIS(a, n));
	return 0;
}