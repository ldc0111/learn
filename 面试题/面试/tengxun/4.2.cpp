/*************************************************************************
	> File Name: 4.2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月20日 星期五 21时39分10秒
 ************************************************************************/

#include<iostream>
#include <queue>
using namespace std;


int main() {
        int n,k,a;
        priority_queue<int, vector<int>,greater<int> > q;
        cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a;
        q.push(a);
            
    }
    long long t = 0;
    for (int i = 0; i < k; i++) {
        while(!q.empty() && q.top() <= t) q.pop();
        if (q.empty()) cout << "0" << endl;
        else cout << q.top() - t << endl;
        if (!q.empty()) t  = q.top(),q.pop();
        //cout << "t:" << t << endl; 
    }

        return 0;

}
