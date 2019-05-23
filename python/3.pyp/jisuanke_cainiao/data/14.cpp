#include <stdio.h>

int main() {
    int n;
    int k;
    int numbers[1000001];
    int m;
    int i,j;

    // 反复读入数字和查找数字的数量
    while(scanf("%d%d", &n, &k)!= EOF){
        
        // 读入给定的数字
        for (i = 0; i < n; i++) {
            scanf("%d", &numbers[i]);
        }

        for (j = 0; j < k; j++) {
            // 读入待查找的数字，
            scanf("%d", &m);

            // 请在下面完成查找读入数字的功能
            int l = 0, r = n - 1,mid;
            while(l <= r){
                mid = (l + r)/2;
                if(numbers[mid] < m){
                    l = mid  + 1;
                }else if(numbers[mid] > m){
                    r = mid - 1;
                }else{
                    printf(j == k - 1 ? "%d\n":"%d ", mid + 1);
                    break;
                }
            }
            if(l > r){
                printf(j == k - 1 ? "0\n":"0 ");
            }
        }
    }
    return 0;
}