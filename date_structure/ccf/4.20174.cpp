/*************************************************************************
	> File Name: 4.20174.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月28日 星期日 16时26分34秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int g[3][3];

void read(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cin >> g[i][j];
        }
    }
}




int game_end(int &ret){
    ret = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            ret += (g[i][j] == 0);
        }
    }
    for(int i = 0; i < 3; i++){
        if(g[i][0] && g[i][0])
    }
}


int main(){
    int n;
    cin >> n;
    while(n--){
        read();
        cout << dfs(1) << endl;
    }

}
