/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月16日 星期一 21时42分09秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int in(string &str,int &ind){
    int temp = 0,tind = ind;
    while(ind < str.length() && str[ind] >= '0' && str[ind] <= '9') {
        temp = temp*10 + (str[ind] - '0');
        ind++;
    }
    if (temp != 0 && str[tind] == '0') return -1;
    if(temp > 255) return -1;
    return 1;
}


int IP4(string &str) {
    int dian = 0;
    for (int i = 0; i < str.length() && dian < 4;i++) {
        if(in(str,i) == -1) return 0;
        if (i < str.length() && str[i] != '.') return 0;
        if(i < str.length() && str[i] == '.') dian++;
    }
    if (dian != 3) return 0;
    return 1;
}

int st(string &str, int &ind){
    if(str[ind] == ':') return -1;
    int cnt = 0;
    while(ind < str.length() && cnt <= 5){
       if(str[ind] >= '0' && str[ind] <= '9' || 
          str[ind] >= 'a' && str[ind] <= 'f' ||
          str[ind] >= 'A' && str[ind] <= 'F'){
              ind++;
              cnt++;
              continue;
          }
        
        if(str[ind] == ':') break;
        else return -1;
    }
    if(cnt > 4) return -1;
    return 1;
}

int IP6(string &str){
    rintf("111");
    int dian = 0;
    for (int i = 0; i < str.length() && dian < 8;i++) {
        if(st(str,i) == -1) return 0;
        if (i < str.length() && str[i] != ':') return 0;
        if(i < str.length() && str[i] == ':') dian++;
    }
    if (dian != 7) return 0;
    return 1;
}



int main() {
    string str;
    cin >> str;
    if (IP4(str)) {
        printf("IPv4\n");
    } else if (IP6(str)){
        printf("IPv6\n");
    }else {
        printf("Neither\n");
    }
    return 0;
}
