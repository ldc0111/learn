#include <iostream>
using namespace std;



int main() {
    int arr[55] = {0,0,1,1}, n;
    for (int i = 4; i < 55; i++) {
        arr[i] = arr[i - 2] + arr[i - 3];
    }
    cin >> n;
    cout << arr[n] << endl;
    return 0;
}