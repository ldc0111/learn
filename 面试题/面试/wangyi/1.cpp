/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月21日 星期六 15时14分34秒
 ************************************************************************/

#include<iostream>
#include<map>
using namespace std;

int main() {
    int n,m,te;
    map<int,int> mp;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> te;
        mp[te]++;
    }
    for (int i = 0; i < m; i++) {
        cin >> te;
        cout << mp[te] << endl;
    }
    

    return 0;
}

