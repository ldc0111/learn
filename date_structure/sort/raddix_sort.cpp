/*************************************************************************
	> File Name: raddix_sort.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月21日 星期日 11时57分29秒
 ************************************************************************/

#include<iostream>
#include <time.h>
#include <string.h>
using namespace std;
/*
void radix_sort(int * num, int n){
    int *temp = (int *)malloc(sizeof(int) * n);
    int cnt[65536] = {0};
    for (int i = 0; i < n; i++) cnt[num[i] & 0xffff]++;
    for (int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];
    for (int i = 65536; i >= 1; i--) cnt[i] = cnt[i - 1];
    cnt[0] = 0;
    for (int i = 0; i < n; i++) temp[cnt[(num[i] & 0xffff)]++] = num[i];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[(temp[i] >> 16) & 0xffff]++;
    for (int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];
    for(int i = 65536; i >= 1; i--) cnt[i] = cnt[i - 1];
    cnt[0] = 0;
    for(int i = 0; i < n; i++) num[cnt[(temp[i] >> 16) & 0xffff]++] = temp[i];
    return ;
}*/

void radix_sort(int *num, int n){
    int *temp = (int *)malloc(sizeof(int) * n);
    int cnt[65537] = {0};
    for(int i = 0; i < n; i++) cnt[(num[i] & 0xffff) + 1]++;
    for(int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];//每个类型的后缀存放的是前面ｎ种类型的总和，也就是种类型后缀的存放的开始位置
    for(int i = 0; i < n; i++) temp[cnt[(num[i] & 0xffff)]++] = num[i];
    memset(cnt,0,sizeof(cnt));
    for(int i = 0; i < n; i++) cnt[((temp[i] >> 16) & 0xffff) + 1]++;
    for(int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];
    for(int i = 0; i < n; i++) num[cnt[(temp[i] >> 16) & 0xffff]++ ] = temp[i];
    return ;
}


int main(){
    srand(time(0));
    int a[100];
    int n = 100;
    for(int i = 0; i <  n; i++){
        a[i] = rand() % (n + 1);
    }
    radix_sort(a,n);
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
