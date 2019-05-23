#include <iostream>
#include <iomanip>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::fixed;
int main() {
    double a,b;
    cin >> a >> b;
    cout << fixed <<setprecision(2) << a + b + sqrt(a * a + b * b) << endl;
    cout << fixed << setprecision(2) << a * b / 2 << endl;

    return 0;
}