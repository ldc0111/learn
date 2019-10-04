/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月17日 星期二 19时49分31秒
 ************************************************************************/

#include <iostream>
#include <string.h>
using namespace std;


int main() {
    char str[85];
    scanf("%[^\n]s",str);
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == 'Z' || str[i] == 'z'){
            str[i] = str[i] - 26;
        } else if(str[i] >= 'a'  && str[i] < 'z' || 
                  str[i] >= 'A' && str[i] < 'Z') {
                str[i] = str[i] + 1;
        }
    }
    
    cout << str << endl;
    return 0;
}
