/*************************************************************************
	> File Name: 3.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月17日 星期二 20时07分32秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;



int main() {
    char a[10005],b[10005];
    while(scanf("%s %s",a,b) != EOF) {
        int alen = strlen(a),blen = strlen(b);
        if(alen < blen) {
            cout << "No" << endl;
        } else{
            int at[26] = {0},bt[26] = {0},flag = 1;
            for (int i = 0; i < alen; i++){
                at[a[i] - 'A'] += 1;
            }
            for (int i = 0; i < blen; i++) {
                bt[b[i] - 'A'] += 1;
            }

            for (int i = 0; i < 26; i++) {
                printf("i = %d, at = %d bt = %d\n",i,at[i],bt[i]);
                if(at[i] >= bt[i]) continue;
                flag = 0;
            }
            if(flag) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }


    return 0;
}
