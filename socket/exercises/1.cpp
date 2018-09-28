/*************************************************************************
	> File Name: 1.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月28日 星期五 12时25分00秒
 ************************************************************************/

#include "head.h"

int main(){
    FILE *fp = popen("./cpu.sh", "r");
    char buffer[max_size];
    while(!feof(fp)) {
        memset(buffer,0,sizeof(buffer));
        fread(buffer,sizeof(char), max_size, fp);
        printf("%s", buffer);
    }
    return 0;
}
