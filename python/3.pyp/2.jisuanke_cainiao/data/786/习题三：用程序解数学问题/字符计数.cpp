#include <stdio.h>
void upper_case_count(char arr[31]) {
    // 请在下面实现统计并输出大写字母个数的功能
    int temp = 0;
    for (int i = 0; arr[i]; i++){
        if(arr[i]>= 'A' && arr[i] <= 'Z') temp++;
    }
    printf("%d\n",temp);
    return 0;
}
void lower_case_count(char arr[31]) {
    // 请在下面实现统计并输出小写字母个数的功能
    int temp = 0;
    for (int i = 0; arr[i]; i++){
        if(arr[i] >= 'a' && arr[i] <= 'z') temp++;
    }
    printf("%d\n",temp);
    return 0;   
}
void digit_count(char arr[31]) {
    // 请在下面实现统计并输出数字个数的功能
    int temp = 0;
    for (int i = 0; arr[i]; i++){
        if(arr[i] >= '0' &&arr[i] <= '9') temp++;
    }
    printf("%d\n",temp);
    return 0;   
}
void space_count(char arr[31]) {
    // 请在下面实现统计并输出空格个数的功能
    int temp = 0;
    for (int i = 0; arr[i]; i++){
        if(arr[i] == ' ') temp++;
    }
    printf("%d\n",temp);
    return 0;   
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
