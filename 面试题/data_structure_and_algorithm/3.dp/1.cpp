/*************************************************************************
> File Name: 1.cpp
> Author: 
> Mail: 
> Created Time: 2019年08月24日 星期六 20时21分44秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define maxn 100000
using namespace std;
int main() {
    long long n,a[maxn + 5] = {0};
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];

    }
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if(a[i] < a[i - 1]) {
            ans++;
            while(a[i] > a[i + 1]) i++;

        }

    }
    cout << ans << endl;

    return 0;

}
