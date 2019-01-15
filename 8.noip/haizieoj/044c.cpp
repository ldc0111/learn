/*************************************************************************
	> File Name: 044c.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月14日 星期一 14时38分58秒
 ************************************************************************/

#include<iostream>
using namespace std;

#define maxn 1000000


int dp[maxn + 5] = {0};
int arr[maxn + 5] = {0};
int f[maxn + 5] = {0};
/*
 10
3 2 5 7 4 5 7 9 6 8
-1 3 
-1 2 
-1 2 5 
-1 2 5 7 
-1 2 4 7 
-1 2 4 5 
-1 2 4 5 7 
-1 2 4 5 7 9 
-1 2 4 5 6 9 
-1 2 4 5 6 8 
 */
int binary_search(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] < x) head = mid;
        else tail = mid - 1;
    }
    return head;
}
void print(int *num, int n) {
    for (int i = 0; i < n; i++) {
        cout << num[i] << " ";
    }
    cout << endl;
}
int main() {
    int n,len = 1; 
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    f[0] = -1;//虚拟位
    //f[i]里面存储的是i长度的最小arr数组元素的值的值
    //这个需要模拟一遍数组内存储的值，当一个值大于这个数的时候他就可以接在这个
    //数的后面，同事证明他小于后面那个数，而如果他可以接在这个数的后面形成的
    //最长上升子序列就和他后面那个位置存储的值的最长上升子序列相同且比后一个值要小
    //所以可以接
    for (int i = 1; i <= n; i++) {
        dp[i] = binary_search(f, len, arr[i]) + 1;
        f[dp[i]] = arr[i];
        if (len <= dp[i]) len += 1;
        //print(f,len);
    }
    cout << len - 1<< endl;
    return 0;
}
