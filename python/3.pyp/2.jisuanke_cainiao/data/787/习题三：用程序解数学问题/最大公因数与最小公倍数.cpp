#include <iostream>
using namespace std;
int gcd(int n, int m);
int lcm(int n, int m);
int main() {
    int n, m;
    cin>>n>>m;  
    cout<<gcd(n,m)<<endl;
    cout<<lcm(n,m)<<endl;

    return 0;
}
int gcd(int n, int m) {
    if (m <= n) {
    // 请在这里继续完成 gcd 函数
        return m != 0 ? gcd(m,n % m) : n;
    } else {
        return gcd(m, n);
    }
}
int lcm(int n, int m) {
// 请在这里继续完成 lcm 函数
    return n * m /gcd(n,m);
}