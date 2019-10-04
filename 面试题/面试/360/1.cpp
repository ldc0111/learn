/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月26日 星期四 20时34分02秒
 ************************************************************************/

#include<iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <string.h>
using namespace std;
//36


int main() {
    int n,a,t;
    double b =1.3;
    double c = 1;
    map<int, int> mp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> t;
        mp[a] = t;
    }
    double ans = 0;
    double v = 0;

    for (auto it = mp.rbegin(); it != mp.rend();it++) {
        ans += v * it->second + 0.5 * it->first * pow(it->second,2);
        
        v += it->second * it->first;
        //cout << ans << " " << v << endl;
    }
    char s[50];
    memset(s,0,sizeof(s));
    sprintf(s,"%0.2f",ans);
    if (s[strlen(s) - 1] > '5') {
        printf("%0.1f\n",ans + 0.1);
    }else {
        printf("%0.1f\n",ans);
    }

    return 0;
}
