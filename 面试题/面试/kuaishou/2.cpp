/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月16日 星期一 22时28分45秒
 ************************************************************************/

#include<iostream>
#include <algorithm>
using namespace std;




int main() {
        int n,a[10000005];
        cin >> n;
    for (int i = 0; i < n; i++) {
                cin >> a[i];
            
    }
    sort(a,a + n);

    return 0;
}
