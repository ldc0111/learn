#include<iostream>
using std::cin;
using std::cout;
using std::endl;
int is_prime(int x){
    if(x < 2) return 0;
    for (int i = 2; i * i <= x; i++) {
        if(x % i == 0) return 0;
    }
    return 1;
}
int main() {
    int x;
    cin >> x;
    if (is_prime(x)) {
       cout << "YES"; 
    } else {
        cout << "NO";
    }
	return 0;
}