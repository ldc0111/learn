#include <cstdio>
#include <iostream>
using namespace std;
#define swap(a,b) {\
	__typeof(a) temp = a;\
	a = b;\
	b = temp;\
}
int main() {
    int n = 10;
    int m;
    int numbers[10];
    int i;

    // 读入给定的数字
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    for (int i = 0; i < n; i++) {
        m = i;
        for (int j = i + 1; j < n; j++) {
            if(numbers[j] > numbers[m]){
                m = j;
            }
        }
        //cout << m << " : "<<endl;
        if(m != i) swap(numbers[i], numbers[m]);
    }
    for (int i = 0; i < n - 1; i++) {
        cout << numbers[i] << " ";
    }
    cout << numbers[9] << endl;

    return 0;
}