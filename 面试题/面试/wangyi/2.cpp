/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月21日 星期六 15时18分58秒
 ************************************************************************/

#include<iostream>
using namespace std;


int main() {
    int t,n,m;
    cin >> t;
    while (t--) {
        int a[100005] = {0};
        cin >> n >> m;
        for (int i = 0; i < n ;i++) {
            cin >> a[i];
        }
        int flag = 1,j = 0;
        if (a[0] > 0) a[0] -= 1;
        for (int i = 1; i < n && flag; i++) {
            if (a[i] == 0) continue;
            if (a[i] - 1 >= a[j]) {
                a[i] -= 1;
            } else if (a[i]== a[j]);
            else if (a[i] + 1 >= a[j]) {
                a[i] += 1;
            } else a[i]
            j = i;
        }
        if (flag) cout << "YES" << endl;
        else cout << "NO" << endl;

    }


    return 0;
}
