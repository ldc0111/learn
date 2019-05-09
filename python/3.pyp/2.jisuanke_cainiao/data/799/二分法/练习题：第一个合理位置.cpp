#include <stdio.h>
int find_first_location(int *num, int len, int target) {
	int l = -1, r = len - 1;
    while(l < r) {
        int mid = (l + r + 1) >> 1;
        if (num[mid] < target) l = mid;
        else r = mid - 1;
    }
    return l + 1;
}
int main() {
	int num[100000];
	int n, m;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &num[i]);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int value;
		scanf("%d", &value);
		printf("%d\n", find_first_location(num, n, value));
	}
	return 0;
}