#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main() {
    int x = 0;
    cin >> x;
    for (int i = 1; i <= x; i++) {
        int j = i;
        for (; j < x; j++) {
            cout << i << "*" << j << "=" << i * j << "\t";
        }
        cout << i << "*" << j << "=" << i * j << endl;
    }

    return 0;
}