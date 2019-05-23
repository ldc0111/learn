#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void hannuota(int x,char a, char b, char c) {
    if(x == 1){
        cout << a << "-->" << c << endl;
    } else {
        hannuota(x - 1, a, c, b);
        cout << a << "-->" << c << endl;
        hannuota(x - 1, b, a, c);
    }
}

int main() {
    int x;
    cin >> x;
    hannuota(x, 'A', 'B', 'C');
    return 0;
}