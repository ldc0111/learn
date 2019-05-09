#include <iostream>
using namespace std;

int main() {
    int matrix[3][3];
    int i;
    int j;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 2; j > 0; j--) {
            cout << matrix[j][i] << " ";
        }
        cout << matrix[0][i] << endl;
    }
    return 0;
}