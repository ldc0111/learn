#include <stdio.h>
#include <stdlib.h>
int* three_sum(int *nums, int length, int target) {
    int *ans = malloc(sizeof(int) * 3);
    int a,b,c,flag = 1;
    for (a = 0; a + 2 < length && flag; a++) {
        b = a + 1;
        c = length - 1;
        int tt = target - nums[a];
        while (b < c && flag) {
            int sum = nums[b] + nums[c];
            if (sum == tt) flag = 0;
            else if (sum < tt) b++;
            else c--;
        }
    }
    ans[0] = a - 1;
    ans[1] = b;
    ans[2] = c;
    //printf("%d %d %d\n", a,b,c);
    return ans;
}
int main() {
    int n, target;
    scanf("%d %d", &n, &target);
    int* num = (int*)malloc(n * sizeof(int));
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", num + i);
        a[i] = num[i];
    }
    int *x = three_sum(num, n, target);
    int *p = three_sum(num, n, target);
    if (p[0] == p[1] || p[0] == p[2] || p[1] == p[2] ) {
        printf("一个数只能用一次!\n");
    } else {
        printf("%d\n", a[p[0]] + a[p[1]] + a[p[2]]);
    }
    free(p);
    free(num);
    free(a);
    return 0;
}