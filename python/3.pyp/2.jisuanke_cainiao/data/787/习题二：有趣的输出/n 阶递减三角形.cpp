#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main() {
    int x;
    cin >> x;
    for (int i = x; i > 0; i--) {
        int j = i;
        for (; j > 1; j--) {
            cout << j << " ";
        }
        cout << j << endl;
    }

    return 0;
}