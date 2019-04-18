/*************************************************************************
	> File Name: bitmap.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年04月18日 星期四 16时26分43秒
 ************************************************************************/

#include<iostream>
#include <time.h>
using namespace std;
class bitmap{
    private: 
    int *a;
    public:
    bitmap(int n) {
        a = new int[n /32 + 1];
    }
    void insert(int x) {
        a[x/ 32] |= 1 << (x % 32);
    }
    bool find(int x) {
        return a[x/32] & 1 << (x % 32);
    }
};

int main() {
    srand(time(0));
    bitmap ma(10000);
    for (int i = 0; i < 10; i++) {
        int temp = rand() % 10;
        if(ma.find(temp)) {
            cout << "chongfu " << temp << endl;
            continue;
        }
        ma.insert(temp);
        cout << "insert " << temp << endl;
    }
    return 0;
}
