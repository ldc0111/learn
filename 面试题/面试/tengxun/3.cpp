/*************************************************************************
> File Name: 3.cpp
> Author: 
> Mail: 
> Created Time: 2019年09月20日 星期五 20时54分39秒
************************************************************************/

#include<iostream>
#include <algorithm>
#include <cmath>
using namespace std;



int main() {
    int tt;
    cin >> tt;
    while (tt--) {
        int t,arr[105] = {0},ans1,ans2;
        cin >> t;
        for (int i = 0; i < t;i++) {
            cin >> arr[i];
        }
        sort(arr,arr + t);
        long long a = 0,b = 0,x = 0,y = t - 1;
        while (y - x >= 3) {
            int ta = arr[y] + arr[x];
            int tb = arr[y - 1] + arr[x + 1];
            if (abs((a + ta) - (b + tb)) <= abs((a + tb) - (b + ta))) {
                a += ta; b += tb;
            } else {
                a += tb; b += ta;
            }
            y -= 2;
            x += 2;
        }
        if(t == 2) {
            ans1 = min(arr[0],arr[1]);
            ans2 = max(arr[0],arr[1]);
        } else if(y > x) {
            int ta = arr[x],tb = arr[y];
            if (abs((a + ta) - (b + tb)) <= abs((a + tb) - (b + ta))) {
                a += ta; b += tb;
            } else {
                a += tb;b += ta;
            }
            y -= 1;
            x += 1;
            if (abs((a + arr[x]) - b) <= abs(a - (b + arr[x]))) {
                a += arr[x];
            } else {    
                b += arr[x];
            }
            ans1 = min(a,b);
            ans2 = max(a,b);
        } else {
            ans1 = min(a,b);
            ans2 = max(a,b);
        }
        cout << ans1 << " " << ans2 << endl;
    }

    return 0;
}
