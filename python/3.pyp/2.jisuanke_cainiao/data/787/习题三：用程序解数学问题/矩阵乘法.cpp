#include <iostream>
using namespace std;

int main() {
    int matrix_a[10][10];
    int matrix_b[10][10];
    int c[10][10] = {0};
    int m;
    int n;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix_a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix_b[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m ; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int j = 0;
        for (; j < m - 1; j++) {
            cout << c[i][j] << " ";
        }
        cout << c[i][j] << endl;
    }
    return 0;
}