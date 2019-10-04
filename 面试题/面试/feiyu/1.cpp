/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月17日 星期二 19时35分45秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int main() {
    map<int,int> mp;
    int a[105],i = 0,ans = 0;
    while(scanf("%d",&a[i]) != EOF){
        i++;
        mp[a[i]] += 1;
    }
    for (int k = 0; k < i; k++) {
        if(mp[a[k]] < (i/2)) continue;
        cout << a[k] << endl;
        break;
    }
    return 0;
}
