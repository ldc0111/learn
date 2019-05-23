#include <stdio.h>
#include <stdlib.h>
int pickMaxSum(int **nums, int length) {
    #define max(a,b) ((a) > (b) ? (a) : (b))
	for(int i = length - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            nums[i][j] += max(nums[i + 1][j], nums[i + 1][j + 1]);
        }
    }
    return nums[0][0];
}
int main() {
	int n;
	scanf("%d", &n);
	int **a = malloc(sizeof(int*) * n);
	for (int i = 0; i < n; ++i) {
		a[i] = malloc(sizeof(int) * (i + 1));
		for (int j = 0; j <= i; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	printf("%d\n", pickMaxSum(a, n));
	return 0;
}