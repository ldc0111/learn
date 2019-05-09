#include <stdio.h>
#include <stdlib.h>

#define max()
#define min(a,b) ((a) < (b) ? (a) : (b))

int find_kth_number(int *num1, int *num2, int n, int k) {
    int x = 0, y = 0;
    while (k > 1) {
        if (x == n) { y = y + k - 1; return num2[y];}
        else if (y == n) { x = x + k - 1; return num1[x];}
        int a,b;
        a = min(k >> 1, n - x);
        b = min(k - (k >> 1), n - y);
        if (num1[x + a - 1] > num2[y + b - 1]) {
            y += b;
            k -= b;
        } else {
            x += a;
            k -= a;
        }
    }
    return min(num1[x],num2[y]);
}
int main() {
	int n;
	scanf("%d", &n);
	int *num1 = malloc(n * sizeof(int));
	int *num2 = malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i) {
		scanf("%d ", &num1[i]);
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d ", &num2[i]);
	}
	int m, tp;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d", &tp);
		printf("%d\n", find_kth_number(num1, num2, n, tp));
	}
	return 0;
}