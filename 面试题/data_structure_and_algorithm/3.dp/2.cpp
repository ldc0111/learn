/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月11日 星期五 22时36分14秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define max_n 6000
struct Edge{
    int to,next;
}g[(max_n << 1) + 5];
int head[max_n + 5],cnt = 0;
int val[max_n + 5];
int dp[max_n + 5][2];
inline void add(int a,int b) {
    g[++cnt] = {b,head[a]};
    head[a] = cnt;
}

void get_dp(int fa,int x) {
    for (int i = head[x]; i; i = g[i].next) {
        int to = g[i].to;
        if (to == fa) continue;
        get_dp(x,to);
        dp[x][0] += max(dp[to][0],dp[to][1]);
        dp[x][1] += dp[to][0];
    }
    return ;
}
int main() {
    int n,a,b;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        //a指向ｂ的边
        //b指向ａ的边
        add(a,b);
        add(b,a);
    }
    get_dp(0,1);
    cout << max(dp[1][0],dp[1][1]) << endl;


    return 0;
}
