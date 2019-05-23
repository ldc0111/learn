/*************************************************************************
	> File Name: k.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月20日 星期四 20时09分58秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max()
int num(int *num1,int *num2, int i, int j, int n){
    if(i >= n) return num2[j];
    else if (j >= n) return num1[i];
    return num1[i] < num2[j] ? num1[i] : num2[j];
}

int find_kth_number(int *num1, int *num2, int n, int k) {
    if(k == 1) return num(num1, num2, 0, 0, n);
    int a = 0,b = 0, x = -1, y = -1;
	while (k > 1) {
        a = k  >> 1;
        b = k - a;
        if(x + a >= n)  { a = n - x - 1; b = k - a;} 
        if (y + b >= n) { b = n - y - 1; a = k - b;}
        //printf("%d %d %d \n", num1[x + a], num2[y + b], k);
        if (num1[x + a] > num2[y + b]) {
            y  += b;
            if (y == n - 1) return num1[x + a];
            k -= b;  
        } else {
            x += a;
            if (x == n - 1) return num2[y + b];
            k -= a;
        }
    }
    return num(num1, num2, x + a, y + b, n);
}
/*
int main() {
	int n;
	scanf("%d", &n);
	int *num1 = (int *)malloc(n * sizeof(int));
	int *num2 = (int *)malloc(n * sizeof(int));
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
}*/

void quick_sort(int *arr, int l, int r) {
    if (l >= r) return ;
    int x = l, y = r, z = arr[l];
    while (x < y) {
        while (x < y && arr[y] > z) y--;
        if (x < y) arr[x++] = arr[y];
        while (x < y && arr[x] < z) x++;
        if (x < y) arr[y--] = arr[x];
    }
    arr[x] = z;
    quick_sort(arr, l ,x - 1);
    quick_sort(arr, x + 1, r);
}

int main() {
    srand(time(0));
    #define maxn 10
    int a[maxn],b[maxn], c[maxn * 2];
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < maxn; j++) {
            a[j] = rand() % 1000;
            b[j] = rand() % 1000;
            c[j] = a[j];
            c[maxn + j] = b[j];
        }
        quick_sort(a, 0, maxn - 1);
        quick_sort(b, 0, maxn - 1);
        quick_sort(c, 0, 2 * maxn - 1);
        //for (int j = 0; j < maxn; j++) {
        //    printf("%d ", a[j]);
        //}
        for (int j = 0; j < maxn; j++) {
            int x1 = find_kth_number(a, b, maxn, j + 1);
            if(x1 != c[j]){ 
            printf("j = %d ,x1 = %d c[j] = %d\n", j, x1, c[j]);
            find_kth_numberde(a, b, maxn, j + 1);
            for (int j = 0; j < maxn; j++) {
                printf("%d ", a[j]);
            }
                printf("\n");
            for (int j = 0; j < maxn; j++) {
                printf("%d ", b[j]);
            }
        }
    }
    }

    return 0;
}


