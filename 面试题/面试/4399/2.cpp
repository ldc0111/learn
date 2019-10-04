/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月25日 星期三 19时40分16秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

#define swap(a,b) {\
    typeof(a) temp = a;\
              a = b;\
              b = temp;\
}

void swapstr(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len >> 1; i++) {
        swap(str[i],str[len - i - 1]);
    }
}

int main() {
    FILE *fa = fopen("a.txt","rb");
    FILE *fb = fopen("b.txt","wb");

    //计算文件长度
    long long len = (long int)((long long)ftell(fa) - (long long)fseek(fa,0,SEEK_END));
    //cout << len << endl;
    int step = 3;
    for (int i = 1; i <= len; i += step) {
        FILE * fat = fseek(fa,i,SEEK_END);
        char *buf;
        fread(buf,step,fat);
        //swapstr(buf);
        fwrite(buf,step,fb);
    }

    fclose(fa);
    fclose(fb);


    return 0;
}
