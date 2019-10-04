/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月20日 星期五 20时22分51秒
 ************************************************************************/

#include<iostream>
#include <algorithm>
using namespace std;

int n;
void quick_sort(int (*a)[2],int l,int r) {
    if (l >= r) return ;
    int x = l,y = r,z = a[l][1];
    int temp = a[l][0];
    while (x < y) {
        if (x < y && a[y][1] >= z) y--;
        if (x < y && a[y][1] < z) {a[x][0] = a[y][0]; a[x][1] = a[y][1]; x++;}
        if (x < y && a[x][1] <= z) x++;
        if (x < y && a[x][1] > z) {a[y][0] = a[x][0]; a[y][1] = a[x][1]; y--;}
    }
    a[x][0] = temp;
    a[x][1] = z;
    //printf("x %d  ,y %d ,z %d\n",x,y,z);
    //for (int i = 0; i < n; i++) cout << a[i][1] << endl;
    //cout << endl;
    quick_sort(a,l,x - 1);
    quick_sort(a,x + 1,r);

}

int main() {
    int m,ans = 0;
    int a[10005][2] = {0},x,y;
    //a[x][0] = 人数,a[x][1] = 拖延值
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    quick_sort(a,0,n - 1);
    x = 0,y = n - 1;
    //for (int i = 0; i < n; i++) cout << a[i][1] << endl;
    //cout << endl;
    while (x <= y) {
        
        int num = a[x][1] + a[y][1];
        if(ans < num) ans = num;
        a[x][0] -= 1;
        if (a[x][0] == 0) x += 1; 
        a[y][0] -= 1;
        if (a[y][0] == 0) y -= 1;

    }
    cout << ans << endl;


    return 0;
}
