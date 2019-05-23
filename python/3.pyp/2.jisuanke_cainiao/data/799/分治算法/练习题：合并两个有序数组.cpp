#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void merge(int *nums, int *nums1, int length1,
                      int *nums2, int length2) {
    int a = 0,b = 0;
    int ind = 0;
    while (a < length1 && b < length2) {
        if(nums1[a] < nums2[b]) {
            nums[ind] = nums1[a++];
        } else {
            nums[ind] = nums2[b++];
        }
        ind++;
    }
    if(a >= length1) {
        while (b < length2) {
            nums[ind++] = nums2[b++];
        }
    }
    if (b >= length2) {
        while (a < length1) {
            nums[ind++] = nums1[a++];
        }
    }
}
int main() {
    int n, m;
    scanf("%d %d",&n, &m);
    int *num = (int*)malloc((n + m) * sizeof(int));
    int *num1 = (int*)malloc(n * sizeof(int));
    int *num2 = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", num1 + i);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d", num2 + i);
    }
    for (int i = 0; i < 1000; ++i) {
        free(num);
        num = (int*)malloc((n + m) * sizeof(int));
        merge(num, num1, n, num2, m);
    }
    for (int i = 0; i < n + m; ++i) {
        printf("%d%c", num[i], i == n + m - 1? '\n' : ' ');
    }
    free(num);
    free(num1);
    free(num2);
    return 0;
}