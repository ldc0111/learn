#include <stdio.h>
int* get_two_sum(int *numbers, int length, int target) {
	int *ans = (int *)malloc(sizeof(int) * 2);
    ans[0]= 0,ans[1] = length - 1;
    while (ans[0] < ans[1]) {
        int sum = numbers[ans[0]] + numbers[ans[1]];
        if (sum == target) return ans;
        if (sum > target) ans[1]--;
        else ans[0]++;
    }
    return ans;
}
int main() {
	int n;
	int v[100000];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &v[i]);
	}
	int x;
	scanf("%d", &x);
	int* ans = get_two_sum(v, n, x);
	printf("%d %d\n", ans[0], ans[1]);
	return 0;
}