/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月24日 星期二 19时47分57秒
 ************************************************************************/

#include<iostream>

using namespace std;

long long gcd(long long a,long long b) {
    if (a < b) swap(a,b);
    return b == 0  ? a : gcd(b,a%b);
}

int main() {
    long long n,a,b;
    cin >> n;
    a = n,b = n - 1;
    cout << a * b /gcd(a,b) - gcd(a,b);


    return 0;
}
