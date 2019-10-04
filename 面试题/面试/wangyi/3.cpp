/*************************************************************************
	> File Name: 3.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月21日 星期六 15时28分23秒
 ************************************************************************/

#include<iostream>
#include <algorithm>
#include <cstdio>
using namespace std;


////00000000001111111111
long long serach(long long *a,long long len,long long te) {
    long long l = 0, r = len;
    while (l < r) {
        long long mid = (l + r) >> 1;
        if (a[mid] < te) l = mid + 1;
        else r = mid;
    }
    return r;
}


int main() {
    int t;
    //cin >> t;
    scanf("%d",&t);
    while (t--) {
        int n,arr[10005] = {0};
        long long a[10005] = {0},len = 1;
        //a数组为下标为长度,里面的值为和
        cin >> n;
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
            //cin >> arr[i];
        }
        a[0] = arr[0];
        for (int i = 1; i < n; i++) {
            //也可以用二分
            long long j = serach(a,len,arr[i]);
            //for (j = 0; j < len; j++) {
            //    if(arr[i] > a[j]) continue;
            //    break;
            //}
            if(j == len) {a[j] = a[j - 1] + arr[i]; len++;}
            else if (j != 0) a[j]  = min(a[j],a[j - 1] +  arr[i]);
            else a[j] = min(a[j],(long long)arr[i]);

            //cout << "j:" << j << endl;
            //for (int c = 0; c < len; c++) {
            //    cout << a[c] << ",";
            //}
            //cout << endl;
        }
        printf("%d\n",len);
        //cout << len << endl;
    }

    return 0;
}
