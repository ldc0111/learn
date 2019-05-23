#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main() {
    int x;
    cin >> x;
    for (int i = 1; i <= x; i++) {
        for (int j = i; j < x; j++) {
            cout << i << " ";
        }
        cout << i << endl;
    }

    return 0;
}