#include <iostream>
using namespace std;

int main() {
    int matrix[100][100];
    int m;
    int n;
    int temp = 0;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
	cin >> temp;
    if(temp) {//1
        for (int i = 0; i < m; i++) {
            for (int j = n - 1; j > 0; j--) {
                cout << matrix[i][j] << " ";
            }
            cout << matrix[i][0] << endl;
        }
    }else {
        for (int i = m - 1; i >= 0; i--) {
            int j = 0;
            for (; j < n - 1; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << matrix[i][j] << endl;
        }
    }
    return 0;
}