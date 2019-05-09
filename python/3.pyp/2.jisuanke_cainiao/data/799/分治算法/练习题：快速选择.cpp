#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(a,b) ((a) < (b) ? (a) : (b))

int quick_select(int *nums, int left, int right, int k) {
    if (left > right) return -1;
    if(left == right) return nums[left];
    int x = left, y = right,z = nums[left];
    while (x < y) {
        while (x < y && nums[y] > z) y--;
        if (x < y) nums[x++] = nums[y];
        while (x < y && nums[x] < z) x++;
        if (x < y) nums[y--] = nums[x];
    }
    nums[x] = z;
    if(x - left + 1 == k) return nums[x];
    else if (x - left + 1 > k) quick_select(nums,left, x - 1,k);
    else quick_select(nums,x + 1, right,k - (x - left + 1));
}
int main() {
    int n, k;
    scanf("%d", &n);
    int *num = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", num + i);
    }
    for (int i = 1; i <= min(100, n); ++i) {
        printf("%d\n", quick_select(num, 0, n - 1, i));
    }
    free(num);
    return 0;
}