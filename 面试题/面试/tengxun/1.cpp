/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月20日 星期五 20时05分18秒
 ************************************************************************/

#include<iostream>
using namespace std;


int find(string & str,char ch) {
    for (int i = 0; i < str.length(); i++) {
        if(str[i] != ch) continue;
        if(str.length() - i >= 11) return 1;
        else return 0;
    }
    return 0;
}


int main() {
    int t,n;
    cin >> t;
    while (t--) {
        string str;
        cin >> n;
        cin >> str;
        if (find(str,'8')) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
