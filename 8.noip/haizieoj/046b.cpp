/*************************************************************************
	> File Name: 046b.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月14日 星期一 20时32分41秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;
#define maxn 500000

int dp[maxn + 5];
vector<int> arr[maxn + 5];
void expand(string &str, int l, int r) {
    if(r >= str.size() && str[l] != str[r]) return ;
    while (l >= 0 && r < str.size() && str[l] == str[r]) {
        arr[r].push_back(l);
        l--,r++;
    }
    return ;
}

int main() {
    string str;
    cin >> str;
    for (int i = 0; i < str.size(); i++) {
        arr[i].push_back(i);//存储以ｉ位置为止里的所有回文串的开始位置
        //sehuhzzexe
        //比如第二个ｈ存储的是，ｕ的下标，和ｅ的下标
        expand(str, i - 1, i + 1);
        expand(str, i, i + 1);
    }
    for (int i = 0; i < str.size(); i++) {
        dp[i] = str.size() - 1;
        for (int k = 0; k < arr[i].size(); k++) {
            int ind = arr[i][k];//根据以ｉ位置为止的回文串的开始位置，那个点算出ｄｐ下标
            int val = (ind - 1 < 0 ? -1: dp[ind - 1]);//根据下标查找到他最少的切割次数，
            //如果是０则说算上ｉ这个串整个是一个回文串，返回－１便于计算
            dp[i] = min(dp[i],val + 1);
        }
    }
    cout << dp[str.size() - 1] << endl;

    return 0;
}
