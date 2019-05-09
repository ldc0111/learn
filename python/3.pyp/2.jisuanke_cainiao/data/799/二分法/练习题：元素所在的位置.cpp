#include <stdio.h>
int binary_search(int target, int *num, int len) {
    int l = 0, r = len - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (num[mid] == target) return mid;
        if (num[mid] > target) r = mid - 1;
        else l = mid + 1;
    }
	return -1;
}
int main() {
	int num[1000000];
	int n, m;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &num[i]);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int value;
		scanf("%d", &value);
		printf("%d\n", binary_search(value, num, n));
	}
	return 0;
}