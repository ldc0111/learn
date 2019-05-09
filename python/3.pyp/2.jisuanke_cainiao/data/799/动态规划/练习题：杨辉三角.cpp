#include <stdio.h>
long long PascalTriangle(int row, int column) {
    if (column == 1 || row == column) return 1;
    long long  arr[2][100000];
    arr[1][1] = 1;
    for (int i = 2; i <= row; i++) {
        int ind = i & 1;
        for (int j = 1; j <= i; j++) {
            arr[ind][j] = arr[ind ^ 1][j] + arr[ind ^ 1][j - 1];
        }
    }
    return arr[row & 1][column];
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	printf("%lld\n", PascalTriangle(n, m));
	return 0;
}