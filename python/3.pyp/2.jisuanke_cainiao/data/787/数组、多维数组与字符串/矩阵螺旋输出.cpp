#include <iostream>
using namespace std;

int main() {
    int matrix[100][100];
    int m;
    int n;
    int num = 0,st = 0,i = 0,j = 0;
    int z = 0,y = 0,s = 0,x = 0;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    z = x = i = j = 0;
    s = m;
    y = n;
    
    for (int k  = 1; k <= n * m; k++) {
        printf(k == n * m ? "%d\n" : "%d ", matrix[i][j]);
        if (st == 0) {
            j++;
            if(j >= y){
                x++;//界
                i++;//
                j--;//本
                st = 1;
            }
        } else if (st == 1) {
            i++;
            if(i >= s){
                y--;//界
                j--;//
                i--;//本
                st = 2;
            }
        } else if (st == 2) {
            j--;
            if (j < z) {
                s--;//界
                i--;//
                j++;//本
                st = 3;
            }
        } else {//st == 3
            i--;
            if(i < x) {
                z++;//界
                j++;//
                i++;//本
                st = 0;
            }
        }
        
    }
    return 0;
}