#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n = 1000000;
int mark[1000001];

int main() {
    int c, a, b;
    memset(mark, 0, sizeof(mark));
    mark[0] = 1;
    mark[1] = 1;

    for (c = 2; c * c <= n; c++) {
		if(mark[c] != 1) {
            for (int j = 2; j <= n / c; j++) {
                mark[c * j] = 1;
            } 
        }
    }
    cin >> a >> b;
    for (int i = b; i <= a; i++) {
        if(mark[i] == 0) cout << i << endl;
    }

    return 0;
}