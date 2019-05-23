#include <stdio.h>
#include <stdlib.h>
int find_target(int **matrix, int n, int m, int target) {
    if (target < matrix[0][0] || target > matrix[n - 1][m - 1]) return 0;
	int l = 0, r = n,mid = 0,flag = 0,x;
    //1111000
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if (matrix[mid][0] < target) l = mid;
        else r = mid - 1;
    }
    x = l;
    l = 0, r = m;
    while (l <= r && !flag) {
        mid = (l + r) >> 1;
        if (matrix[x][mid] == target) flag = 1;
        if (matrix[x][mid] > target) r = mid - 1;
        else l = mid + 1;
    }
    return flag;
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int ** v;
	v = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < m; ++i) {
		v[i] = (int*)malloc(m * sizeof(int));
	}
	int tp;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j){
			scanf("%d", &v[i][j]);
		}
	}
	int tot;
	scanf("%d", &tot);
	for (int i = 0; i < tot; ++i) {
		scanf("%d", &tp);
		if (find_target(v, n, m, tp)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}