#include <iostream>
using namespace std;
void upper_case_count(char arr[31]) {
    // 请在下面实现统计并输出大写字母个数的功能
    int temp = 0;
    for (int i = 0; arr[i]; i++) {
        if(arr[i] >= 'A' && arr[i] <= 'Z') {
            temp++;
        }
    }
    cout << temp << endl;
    return ;
}
void lower_case_count(char arr[31]) {
    // 请在下面实现统计并输出小写字母个数的功能
    int temp = 0;
    for (int i = 0; arr[i]; i++) {
        if(arr[i] >= 'a' && arr[i] <= 'z') {
            temp++;
        }
    }
    cout << temp << endl;
    return ;
}
void digit_count(char arr[31]) {
    // 请在下面实现统计并输出数字个数的功能
    int temp = 0;
    for (int i = 0; arr[i]; i++) {
        if(arr[i] >= '0' && arr[i] <= '9') {
            temp++;
        }
    }
    cout << temp << endl;
    return ;
}
void space_count(char arr[31]) {
    // 请在下面实现统计并输出空格个数的功能
    int temp = 0;
    for (int i = 0; arr[i]; i++) {
        if(arr[i] == ' ') {
            temp++;
        }
    }
    cout << temp << endl;;
    return ;
}

int main() {
    char string[31];
    int i;
	scanf("%[^\n]s",string);
    
    upper_case_count(string);
    lower_case_count(string);
    digit_count(string);
    space_count(string);
    return 0;
    
}
