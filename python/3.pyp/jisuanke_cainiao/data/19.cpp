#include <stdio.h>


int main() {
    int matrix[100][100];
    int n, m;
    int shang,xia,zuo,you;
    int x = 1,y = 1,st = 1;
    
    scanf("%d %d",&n, &m);
    shang  = 1, zuo = 1, xia = n, you = m;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    for (int i = 1; i <= m * n; i++){
        printf(i == m * n ? "%d\n" : "%d ", matrix[x][y]);
        if (st == 1) {
            if (y < you) {
                y++;
            } else {
                //y--;
                x++;
                shang++;
                st = 2;
            }
        } else if (st == 2) {
            if (x < xia){
                x++;
            } else {
                //x--;
                y--;
                you--;
                st = 3;
            }
        } else if (st == 3) {
            if (y > zuo){
                y--;
            } else {
                //y++;
                x--;
                xia--;
                st = 4;
            }       
        } else { //st == 4;
            if (x  > shang) {
                x--; 
            } else {
                //x++;
                y++;
                zuo++;
                st = 1;
            }
        }
    }
    return 0;
}