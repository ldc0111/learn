#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
void quick_sort(char (*str)[25],int l, int r) {
    if(l >= r) return ;
    int x = l, y = r;
    char z[25];
    strcpy(z, str[l]);
    while (x < y) {
        while (x < y && strcmp(str[y], z) >= 0) y--;
        if(x < y) strcpy(str[x++],str[y]);
        while (x < y && strcmp(str[x], z) <= 0) x++;
        if(x < y) strcpy(str[y--],str[x]);
    }
    strcpy(str[x], z);
    quick_sort(str, l, x - 1);
    quick_sort(str, x + 1, r);
    return ;
}

int main() {
    char name[15][25];
    for (int i = 0; i < 10; i++) {
        cin >> name[i];
    }
    quick_sort(name, 0, 9);
    for (int i = 0; i < 10; i++) {
        cout << name[i] << endl;
    }
    return 0;
}