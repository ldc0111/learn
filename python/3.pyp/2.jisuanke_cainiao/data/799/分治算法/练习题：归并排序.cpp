#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void merge_sort(int *nums, int left, int right) {
    if(left >= right) return ;
    if(right-left == 1) {
        if(nums[left] > nums[right]) {
            nums[left] ^= nums[right];
            nums[right] ^= nums[left];
            nums[left] ^= nums[right];
        }
        return ;
    }
    int x = (left + right) >> 1;
    merge_sort(nums,left,x);
    merge_sort(nums,x + 1,right);
    int *arr = (int *)malloc(sizeof(int) * (right - left + 1));
    int a = left,b = x + 1,ind = 0;
    while (a <= x && b <= right) {
        if(nums[a] <= nums[b]) {
            arr[ind] = nums[a++];
        } else {
            arr[ind] = nums[b++];
        }
        ind++;
    }
    while (a <= x) {
        arr[ind++] = nums[a++];
    }
    while (b <= right) {
        arr[ind++] = nums[b++];
    }
    for (int i = 0; i < ind; i++) {
        nums[left + i] = arr[i];
    }
    return ;
}
int main() {
    int n;
    scanf("%d", &n);
    int *num = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", num + i);
    }
    merge_sort(num, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        printf("%d%c", num[i], i == n - 1? '\n' : ' ');
    }
    free(num);
    return 0;
}